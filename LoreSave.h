#ifndef __LORE_SAVE_H__
#define __LORE_SAVE_H__

#include <fstream>
#include <string>

#include "./Lore.h"

bool LoreSave(const Lore& lore, const std::string& parentDir) {
  std::ofstream outLore(parentDir+std::string("/")+lore.getTitle(), std::ofstream::trunc | std::ofstream::out);
  if(!outLore) return false;
  
  for(std::string s: lore.listPages()) {
    outLore << s << '\n';
    LorePage* page = lore.getPage(s);

    std::ofstream outPage(parentDir+std::string("/")+page->getTitle(), std::ofstream::trunc | std::ofstream::out);
    if(!outPage) {
      outLore.close();
      return false;
    }
    
    for(Entry* e : page->getEntries()) {
      outPage << e->getTitle() << '\n';
      outPage << e->getContent() << '\n';
      for(std::string assoc : e->getAssociatedLorePages()) outPage << assoc << ",";
      outPage << '\n';
    }
    outPage.close();
  }
  outLore.close();
  return true;
}

#endif
