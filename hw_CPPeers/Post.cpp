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

#include "Post.h"

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}



vector<string> Post::findTags() {
  // TODO(student): extracts candidate tags based on occurrences of # in the post

  vector<string> finalVec;
  std::stringstream strStream1(this->postText);
  string literal;

  while (!strStream1.eof()) {

      strStream1 >> literal;

      if (literal.at(0) == '#') {

            string tag = "";

            for (char c : literal) {
                switch (c) {
                case '!':
                      continue;
                case ',':
                      continue;
                case '.':
                      continue;
                case '?':
                      continue;
                default:
                      tag += tolower(c);
                }
            }
              

            finalVec.push_back(tag);
      }
  }

  return finalVec;
  

}

/*
vector<string> finalVec;

  string postReadText = getPostText();
  std::stringstream reaStream(postText);

  bool contHash = false;


  while(!reaStream.eof()){

    reaStream >> postReadText;

    if (postReadText.at(0) == '#'){

      for(int i = 1; i <= postReadText.size(); ++i){

        if (postReadText.at(i) == '!'){
          postReadText.erase(i,1);
        }

        if (postReadText.at(i) == ','){
          postReadText.erase(i,1);
        }

        if (postReadText.at(i) == '.'){
          postReadText.erase(i,1);
        }
        if (postReadText.at(i) == '?'){
          postReadText.erase(i,1);
        }

        for(int i = 0; i < postReadText.size(); i++){

          postReadText.at(i) = tolower(postReadText.at(i));

        }

      }

      finalVec.push_back(postReadText);

    
    }

  }


  return finalVec;
*/



