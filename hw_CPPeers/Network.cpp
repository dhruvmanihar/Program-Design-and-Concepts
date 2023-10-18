/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  // TODO(student): load user and post information from file

  std::ifstream infs (fileName);

  std::string inL = "";

  std::string p1 = "";
  std::string fPar = "";

  std::string sPar = "";
  int sParCount = 0;


  std::string tPar = "";
  std::string finOut = "";

  int count = 0;


  if(infs.is_open()){
    while(getline(infs, inL)){
        std::stringstream reader(inL);
        while(!reader.eof()){
          reader >> p1;
        
          if (count == 0 && !(p1 == "Post" || p1 == "User")){
            throw std::runtime_error("Neither Post nor User");
          }

          if (count == 0){
            fPar = p1;
          }

          if (fPar == "User" && count == 1){
            if (count == 1){
              sPar = p1;
            }
            try{
              addUser(sPar);
            }
            catch(...){
              throw std::runtime_error("addUser failed!");
            }
            
          }

          if (fPar == "Post"){
            if (count == 1){
              sPar = p1;
           
              bool isDigit = true;
              for(int i = 0; i < p1.length(); i++){
                if( !( isdigit(p1.at(i)) ) ){
                  isDigit = false;
                }
              }

         
              if ( !(isDigit) ){ 
                throw std::runtime_error("Second p1 is not a digit");
              }

             
              sParCount = stoi(sPar);


            }
            if (count == 2){
              tPar = p1;
            }

            if (count >= 3){ 
              finOut += p1 + " "; 
            }
          }


          count++;
        }


        if(count < 2){
          throw std::runtime_error("Only one thing in this inL!");
        }
        if(fPar == "Post"){ 
          try{
            finOut.erase(finOut.length()-1, 1);
            addPost(sParCount, tPar, finOut);
          }
          catch(...){
            throw std::runtime_error("Adding post did not work!");
          }
        }

        finOut = "";
        count = 0;
    }
  }
  else{
    throw std::invalid_argument("File could not be opened!");
  }

}

void Network::addUser(string userName) {
  // TODO(student): create user and add it to network
  
  for (int i = 0; i < userName.length(); i++){
    userName[i] = tolower(userName[i]);
  }


  for (int i = 0; i < users.size(); i++){
    if (users[i]->getUserName() == userName){
      throw std::invalid_argument("UserName exists");
    }
  }


  User* newUser = new User(userName);
	users.push_back(newUser);
  std::cout << "Added User " << userName << std::endl;

}

void Network::addPost(unsigned int postId, string userName, string finOut) {
  // TODO(student): create post and add it to network

  bool userExists = false;

  for (int i = 0; i < users.size(); i++){
    if (users.at(i)->getUserName() == userName){
      userExists = true;
    }
  }

  if (!userExists){
    throw std::invalid_argument("User does not exist");
  }


  for (int i = 0; i < posts.size(); i++){
    if (posts.at(i)->getPostId() == postId){
      throw std::invalid_argument("Post already exists");
    }
  }

 
  Post* newPost = new Post(postId, userName, finOut);
  posts.push_back(newPost);

  for (int i = 0; i < users.size(); i++){
    if (userName == users.at(i)->getUserName()){
      users.at(i)->addUserPost(newPost);
    }
  }

  
  vector<std::string> postHashtags = newPost->findTags();

  bool alreadyExists = false;
  for (int i = 0; i < postHashtags.size(); i++){
    alreadyExists = false;
    for(int j = 0; j <  tags.size(); j++){
      if (postHashtags.at(i) == tags.at(j)->getTagName() ){
        alreadyExists = true;
        tags.at(j)->addTagPost(newPost);
        break;
      }
    }
    if (!alreadyExists){
      try{
        Tag* newTag = new Tag(postHashtags.at(i));
        newTag->addTagPost(newPost);
        tags.push_back(newTag);
      }catch(...){
        continue;
      }      

    }

  }

  std::cout << "Added Post " << postId << " by " << userName << std::endl;
}

vector<Post*> Network::getPostsByUser(string userName) {
  // TODO(student): return posts created by the given user

  if (userName.empty()){
      throw std::invalid_argument("User name cannot be empty");
  }
     for (User* user : this->users){

        if (user->getUserName() == userName){
            return user->getUserPosts();
        }
     }

     throw std::invalid_argument("User " + userName + " does not exist in the network.");
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  // TODO(student): return posts containing the given tag

  if (tagName == ""){
    throw std::invalid_argument("Given Tag is blank");
  }

  for (int i = 0; i < tags.size(); i++){
    if (tags.at(i)->getTagName() == tagName){
      return tags.at(i)->getTagPosts();
    }
  }

  throw std::invalid_argument("Tag does not exist!");
}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts

  vector<string> popularTags;
	
	if(tags.size() == 0)
		return popularTags;
	
	popularTags.push_back((*tags.at(0)).getTagName());
	int max = (*tags.at(0)).getTagPosts().size();
	
	for(int x = 1; x < tags.size(); x++){

		int temp = (*tags.at(x)).getTagPosts().size();

		if(temp > max){
			popularTags.clear();
			popularTags.push_back((*tags.at(x)).getTagName());
			max = temp;
    }
		else{
			if(temp == max)
				popularTags.push_back((*tags.at(x)).getTagName());
    }
	
  }
	return popularTags;

}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
