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

    /**
     * Adds an already constructed Entry to this LorePage.
     * if an Entry with the same name as the specified Entry
     * already exists in this LorePage, nothing happens.
     */
    void addEntry(Entry* e) {
      for(Entry* all : this->entries) {
        if(all->getTitle() == e->getTitle()) return;
      }
      this->entries.push_back(e);
    };

    /**
     * Removes the Entry with the specified name from this 
     * LorePage. If no Entry with the specified name exists
     * in this LorePage, nothing happens.
     **/
    void removeEntry(std::string entryTitle) {
      for(auto it = this->entries.begin(); it != this->entries.end(); it++) {
        if((*it)->getTitle() == entryTitle) {
          delete (*it);
          this->entries.erase(it);
          break;
        }
      }
    }

    /**
     * Returns the title of this LorePage.
     **/
    const std::string& getTitle() const { return this->title; };

    /** 
     * Returns a vector containing pointers to all the Entry 
     * objects contained within this LorePage.
     **/
    const std::vector<Entry* >& getEntries() const { return this->entries; };
};

#endif
