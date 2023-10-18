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
#include "User.h"

using std::string;
using std::vector;

User::User(string userName) : userName(userName) /* TODO(student): initialize */ {
  // TODO(student): implement constructor checks

  if(userName == ""){
		throw std::invalid_argument("Empty");
  }

  int checkLetter = userName[0];

	if(checkLetter > 122 || checkLetter < 97){
		throw std::invalid_argument("First letter not uppercase");
  }

  for(int i = 0; i < userName.length(); i++){
    
    int upCheck = userName[i];

		if(upCheck >= 65 && upCheck <= 90){
			throw std::invalid_argument("Has capitals");
    }

  }

}

string User::getUserName() {
  // TODO(student): implement getter
  return userName;
}

vector<Post*>& User::getUserPosts() {
  // TODO(student): implement getter
  return userPosts;
}

void User::addUserPost(Post* post) {
  // TODO(student): add post to user posts

  if (post == nullptr){
    throw std::invalid_argument("nullptr");
  }
  
  userPosts.push_back(post);
  

}
