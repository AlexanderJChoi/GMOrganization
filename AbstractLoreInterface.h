#ifndef __ABSTRACT_LORE_INTERFACE_H__
#define __ABSTRACT_LORE_INTERFACE_H__

#include <unordered_map>
#include <vector>
#include <string>
#include <utility>

#include "./Lore.h"
#include "./LorePage.h"
#include "./Entry.h"
#include "./LoreSave.h"
#include "./LoreLoad.h"

class AbstractLoreInterface {
  private:
    std::vector<std::string> listOfLoreNames;
    std::unordered_map<std::string, Lore* > loreCollection;

    virtual bool getSelectedDir(std::string& dirName) = 0;
    virtual bool getSelectedFile(std::string& fileName) = 0;

    virtual bool getNewLoreInfo(Lore*& newLore) = 0;
    virtual bool getNewLorePageInfo(LorePage*& page) = 0;
    virtual bool getNewLorePageEntryInfo(Entry*& entry) = 0;
    
    virtual bool getSelectedLore(std::string& loreName) = 0;
    virtual bool getSelectedLorePage(std::string& loreName, std::string& lorePageName) = 0;
    virtual bool getSelectedLoreEntry(std::string& loreName, std::string& lorePageName, std::string& lorePageEntryName) = 0;

    virtual void handleLoreNotFound() const = 0;
    virtual void handleLorePageNotFound() const = 0;
    virtual void handleLorePageEntryNotFound() const = 0;

    virtual void handleUnableToCreateLore() const = 0;
    virtual void handleUnableToCreateLorePage() const = 0;
    virtual void handleUnableToCreateLorePageEntry() const = 0;

  public:
    virtual ~AbstractLoreInterface() { 
      for(std::pair<std::string, Lore* > p : loreCollection) delete p.second;
      };

    /**
     * Loads a lore collection from a file.
     * File is specified by the getSelectedFile() method.
     * File is read by the global LoadLore() method. 
     * 
     * Returns a boolean indicating success of loading the 
     * specified collection. True indicates a success, false 
     * indicates an error. 
     *
     * Errors include:
     *  a file could not be successfully selected
     *  a Lore collection of the same name is already loaded
     *  LoadLore returns with an error 
     */
    bool loadLore() {
      std::string fileName;
      if(!this->getSelectedFile(fileName)) return false;                              //select a file; return if a file could not be successfully selected

      std::string dir = fileName.substr(0, fileName.find_last_of("/"));               //separate the directory from the fileName
      fileName = fileName.substr(fileName.find_last_of("/") + 1, std::string::npos);

      for(std::string s: this->listOfLoreNames) if(s == fileName) return false;        //return if a Lore collection of the same name is already loaded

      Lore* loadedLore = LoreLoad(fileName, dir);                                     //read the selected Lore file
      if(loadedLore == nullptr) return false;                                         //return if the Lore collection could not be successfully loaded

      std::string loreName = loadedLore->getTitle();                                   //add loadedLore to the database
      this->listOfLoreNames.push_back(loreName);
      this->loreCollection.emplace(loreName, loadedLore);

      return true;
    };
    
    /**
     * Saves a lore collection to a directory.
     * Lore collection is specified by the getSelectedLore() method.
     * Directory is specified by the getSelectedDir() method.
     * Lore is saved using the global LoreSave() function.
     *
     * Returns a boolean indicating the success of saving the 
     * specified Lore collection. True indicates a success, 
     * false indicates an error.
     *
     * Errors include:
     *  a directory could not be successfully selected
     *  a lore collection could not be successfully selected
     *  LoreSave() returns with an error
     */
    bool saveLore() {
      std::string directory;
      if(!this->getSelectedDir(directory)) return false;                    //returns if a directory could not be successfully selected

      std::string loreName;
      if(!this->getSelectedLore(loreName)) return false;                    //returns if a lore collection could not be successfully selected

      if(!LoreSave(*loreCollection.at(loreName), directory)) return false;  //returns if the lore collection could not be successfully saved

      return true;
    };

    /**
     * Creates a new Lore collection in the database.
     * Lore collection is specified by the getNewLoreInfo() method.
     *
     * Returns a boolean indicating the success of creating the 
     * specified Lore collection. True indicates the success, false
     * indicates an error. 
     *
     * Errors include: 
     *  a lore object could not be successfully initialized with correct info
     *  a lore collection of the same name already exists
     */
    bool createNewLore() {
      Lore* newLore;
      if(!this->getNewLoreInfo(newLore)) return false;                                        //returns if a Lore object could not be successfully initialized with correct info
      
      std::string loreName = newLore->getTitle();
      for(std::string s: this->listOfLoreNames) if(s == loreName) return false;               //returns if a Lore collection of the same name already exists
      
      this->listOfLoreNames.push_back(loreName);
      this->loreCollection.emplace(loreName, newLore);
      
      return true;
    };

    bool createNewLorePage() {};
    bool removeLorePageFrom() {};
    bool addNewEntryToLorePageFrom() {};
    bool editEntryToLorePageFrom() {};
    bool removeEntryFromLorePageFrom() {};
    
    /**
     * Returns a vector of the names of all loaded Lore collections in string form
     *
     **/
    const std::vector<std::string>& listLoreNames() const {
      return this->listOfLoreNames;
    };
    
    /**
     * Returns a vector of the names of all LorePages in the specified Lore collection *fromLore*
     * throws a std::out_of_range if the Lore collection does not exist
     **/
    const std::vector<std::string>& listLorePageNames(std::string fromLore) const {
      try {
        Lore* lore = loreCollection.at(fromLore);
        return lore->listPages();
      } catch (std::out_of_range exception) {
        this->handleLoreNotFound();
        throw exception;
      }
    };
    
    /**
     * Returns a vector of all Entry pointers in the specified LorePage *fromLorePage*  from the specified Lore collection *fromLore*
     * throws a std::out_of_range if *fromLore* is not loaded
     * throws a std::out_of_range if *fromLorePage* does not exist within *fromLore*
     **/
    const std::vector<Entry* >& listLorePageEntries(std::string fromLore, std::string fromLorePage) const {
      Lore* lore;
      try {
        lore = loreCollection.at(fromLore);
      } catch (std::out_of_range exception) {
        this->handleLoreNotFound();
        throw exception;
      }
      try {  
        LorePage* page = lore->getPage(fromLorePage);
        return page->getEntries();
      } catch (std::out_of_range exception) {
        this->handleLorePageNotFound();
        throw exception;
      }
    };

};

#endif
