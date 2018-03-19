#ifndef __LORE_PAGE_H__
#define __LORE_PAGE_H__

#include <string>
#include <vector>

#include "./Entry.h"

class LorePage {
  private:
    std::string title;
    std::vector<Entry* > entries;
  public:
    LorePage(std::string t) : title(t) {} ;
    ~LorePage() {
      for(Entry* e : this->entries) {
        delete e;
      }
    };

    void addEntry(Entry* e) {
      for(Entry* all : this->entries) {
        if(all->getTitle() == e->getTitle()) return;
      }
      this->entries.push_back(e);
    };

    void removeEntry(std::string entryTitle) {
      for(auto it = this->entries.begin(); it != this->entries.end(); it++) {
        if((*it)->getTitle() == entryTitle) {
          delete (*it);
          this->entries.erase(it);
          break;
        }
      }
    }

    const std::string& getTitle() const { return this->title; };
    const std::vector<Entry* >& getEntries() const { return this->entries; };
};

#endif
