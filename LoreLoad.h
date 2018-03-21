#ifndef __LORE_LOAD_H__
#define __LORE_LOAD_H__

#include <fstream>
#include <string>
#include <cstring>
#include <vector>

#include "./Lore.h"

Lore* LoreLoad(const std::string& loreTitle, const std::string& parentDir) {
  std::ifstream inFS(parentDir+std::string("/")+loreTitle);
  if(!inFS) return nullptr;
  
  Lore* lore = new Lore(loreTitle);

  std::string nextTitle;
  while(std::getline(inFS, nextTitle)) {
    std::ifstream inLorePage(parentDir+std::string("/")+nextTitle);
    if(!inLorePage) {
      inFS.close();
      delete lore;
      return nullptr;
    }

    LorePage* page = new LorePage(nextTitle);
    std::string entryTitle, entryContent, entryAssoc;
    while(std::getline(inLorePage, entryTitle) && std::getline(inLorePage, entryContent) && std::getline(inLorePage, entryAssoc)) {
      std::vector<std::string> assoc;

      size_t end_of_next_association = entryAssoc.find_first_of(",");
      while(end_of_next_association != std::string::npos) {
        assoc.push_back(entryAssoc.substr(0, end_of_next_association));
        entryAssoc = entryAssoc.substr(end_of_next_association + 1, std::string::npos);
        end_of_next_association = entryAssoc.find_first_of(",");
      }

      page->addEntry(new Entry(entryTitle, entryContent, assoc));
    }
    lore->addPage(nextTitle, page);
    inLorePage.close();
  }
  inFS.close();
  return lore;
}

#endif
