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

#include "Tag.h"



using std::string;
using std::vector;

Tag::Tag(string tagName) : tagName(tagName) /* TODO(student): initialize */ {
  // TODO(student): implement constructor checks

  if (tagName.length() < 2 || tagName[0] != '#'){
    throw std::invalid_argument("Error Tag");
  }

  if (tagName[tagName.length() - 1] == '!' || tagName[tagName.length() - 1] == ',' || tagName[tagName.length() - 1] == '.' || tagName[tagName.length() - 1] == '?'){
    throw std::invalid_argument("Error Tag");
  }

  int checkInt = tagName[1];

  if (checkInt < 97 || checkInt > 122 ){
    throw std::invalid_argument("Error Tag");
  }

  
  int iterTag = 0;
  for(int i = 1; i < tagName.length(); i++){ 
    iterTag = tagName[i];

    if (iterTag >= 65 && iterTag <= 90){

      throw std::invalid_argument("Tag has capital letter");
    }
  }
  
}

string Tag::getTagName() {
  // TODO(student): implement getter
  return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  // TODO(student): implement getter
  return tagPosts;
}

void Tag::addTagPost(Post* post) {
  // TODO(student): add post to tag posts

  if (post == nullptr){
    throw std::invalid_argument("nullptr");
  }
  
  tagPosts.push_back(post);

}
