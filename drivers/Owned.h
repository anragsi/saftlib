/** Copyright (C) 2011-2016 GSI Helmholtz Centre for Heavy Ion Research GmbH 
 *
 *  @author Wesley W. Terpstra <w.terpstra@gsi.de>
 *
 *******************************************************************************
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************
 */
#ifndef OWNED_H
#define OWNED_H

#include "interfaces/iOwned.h"
#include "BaseObject.h"

namespace saftlib {

class Owned : public BaseObject, public iOwned
{
  public:
    Owned(const std::string& objectPath, sigc::slot<void> destroy_ = sigc::slot<void>());
    ~Owned();
    
    void Disown();
    void Own();
    void Destroy();
    std::string getOwner() const;
    bool getDestructible() const;
    
    // use this at the start of protected methods
    void ownerOnly() const;
    // only use this immediately after object creation
    void initOwner(const std::shared_ptr<saftbus::Connection>& connection, const std::string& owner);
    
  protected:
    virtual void ownerQuit();
    static void owner_quit_handler(
      const std::shared_ptr<saftbus::Connection>&,
      const std::string&, const std::string&, const std::string&,
      const std::string&, const saftbus::Serial&, Owned* self);
  
  private:
    sigc::slot<void> destroy;
    sigc::slot<void> unsubscribe;
    std::string owner;
};

}

#endif
