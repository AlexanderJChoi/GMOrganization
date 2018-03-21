#ifndef __LORE_H__
#define __LORE_H__

#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>

#include "./LorePage.h"

class Lore {
  private:
    std::string title;
    std::vector<std::string> lore_page_names;
    std::unordered_map<std::string, LorePage* > pages;
  public:
    Lore(const std::string& t) : title(t) {};
    ~Lore() { 
      for(std::string S : this->lore_page_names) {
        delete this->pages.at(S);
      }
    };
    
    /**
     * Adds an already constructed LorePage to this Lore collection, 
     * if a LorePage of the same name already exists in this Lore 
     * collection, nothing happens.
     **/
    void addPage(const std::string& name, LorePage* page) {
      for(std::string names : this->lore_page_names) {
        if(names == name) return;
      }
      this->lore_page_names.push_back(name);
      this->pages.emplace(name, page);
    };
    
    /**
     * Returns the LorePage in this Lore collection which has the 
     * specified name.
     * throws an std::out_of_range exception if there is no LorePage 
     * with the specified name in this Lore collection
     **/
    LorePage* getPage(const std::string& name) const {
      LorePage* page = 0;
      try {
        page = this->pages.at(name);
      } catch (const std::out_of_range& oor) {
        throw oor;
      }
      return page;
    };
    
    /**
     * Removes the specified LorePage from this Lore collection.
     * If there is no LorePage with the specified name in this 
     * Lore collection, nothing happens.
     **/
    void removePage(const std::string& name) {
      this->lore_page_names.erase(std::remove(this->lore_page_names.begin(), this->lore_page_names.end(), name), this->lore_page_names.end());
      this->pages.erase(name);
    };

    /**
     * Returns the title of this Lore collection.
     */
    const std::string& getTitle() const { 
      return this->title;
    };

    /**
     * Returns a vector containing the names of all the LorePages 
     * in this Lore collection.
     **/
    const std::vector<std::string>& listPages() const {
      return this->lore_page_names;
    };
};

#endif

