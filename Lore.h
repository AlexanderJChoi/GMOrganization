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

    void addPage(const std::string& name, LorePage* page) {
      for(std::string names : this->lore_page_names) {
        if(names == name) return;
      }
      this->lore_page_names.push_back(name);
      this->pages.emplace(name, page);
    };
    
    LorePage* getPage(const std::string& name) const {
      LorePage* page = 0;
      try {
        page = this->pages.at(name);
      } catch (const std::out_of_range& oor) {
        throw oor;
      }
      return page;
    };
    
    void removePage(const std::string& name) {
      this->lore_page_names.erase(std::remove(this->lore_page_names.begin(), this->lore_page_names.end(), name), this->lore_page_names.end());
      this->pages.erase(name);
    };

    const std::string& getTitle() const { 
      return this->title;
    };

    const std::vector<std::string>& listPages() const {
      return this->lore_page_names;
    };
};

#endif

