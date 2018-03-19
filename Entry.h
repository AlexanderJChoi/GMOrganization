#ifndef __ENTRY_H__
#define __ENTRY_H__

#include <string>
#include <vector>

class Entry {
  private:
    std::string title, content;
    std::vector<std::string> assoc_pages;
  public:
    Entry(const std::string& t, const std::string& c, std::vector<std::string>& p) : title(t), content(c), assoc_pages() {
      this->assoc_pages.swap(p);
    }

    const std::string& getTitle() const { return this->title; };
    const std::string& getContent() const { return this->content; };
    const std::vector<std::string>& getAssociatedLorePages() const { return this->assoc_pages; };
};

#endif
