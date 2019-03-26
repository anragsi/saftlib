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
 
 
 
/*
	d-bus interface for FunctionGenerator
	uses FunctionGeneratorImpl
*/

 
#ifndef FUNCTION_GENERATOR_H
#define FUNCTION_GENERATOR_H

#include <deque>


#include "interfaces/FunctionGenerator.h"
#include "FunctionGeneratorImpl.h"
#include "Owned.h"

namespace saftlib {

class TimingReceiver;

class FunctionGenerator : public Owned, public iFunctionGenerator
{
	
  public:
    typedef FunctionGenerator_Service ServiceType;
    struct ConstructorType {
      std::string objectPath;
      std::shared_ptr<TimingReceiver> dev;
 			std::shared_ptr<FunctionGeneratorImpl> functionGeneratorImpl;            
    };
    
    static std::shared_ptr<FunctionGenerator> create(const ConstructorType& args);
    
    // iFunctionGenerator overrides
    void Arm();
    void Abort();
    uint64_t ReadFillLevel();
    bool AppendParameterSet(const std::vector< int16_t >& coeff_a, const std::vector< int16_t >& coeff_b, const std::vector< int32_t >& coeff_c, const std::vector< unsigned char >& step, const std::vector< unsigned char >& freq, const std::vector< unsigned char >& shift_a, const std::vector< unsigned char >& shift_b);
    void Flush();
    uint32_t getVersion() const;
    unsigned char getSCUbusSlot() const;
    unsigned char getDeviceNumber() const;
    unsigned char getOutputWindowSize() const;
    bool getEnabled() const;
    bool getArmed() const;
    bool getRunning() const;
    uint32_t getStartTag() const;
    uint32_t ReadExecutedParameterCount();
    void setStartTag(uint32_t val);
    
  protected:
    FunctionGenerator(const ConstructorType& args);
    ~FunctionGenerator();
    void Reset();
    void ownerQuit();
            
    std::shared_ptr<TimingReceiver> dev;
    
    void on_fg_running(bool);
    void on_fg_armed(bool);
    void on_fg_enabled(bool);
    void on_fg_refill();
    void on_fg_started(uint64_t);
    void on_fg_stopped(uint64_t, bool, bool, bool);

    /*
    std::shared_ptr<FunctionGeneratorChannelAllocation> allocation;
    eb_address_t shm;
    eb_address_t swi;
    etherbone::sdb_msi_device base;
    sdb_device mbx;
    unsigned num_channels;
    unsigned buffer_size;
    unsigned int index;
    unsigned char scubusSlot;
    unsigned char deviceNumber;
    unsigned char version;
    unsigned char outputWindowSize;
    eb_address_t irq;

    int channel; // -1 if no channel assigned
    bool enabled;
    bool armed;
    bool running;
    bool abort;
    sigc::connection resetTimeout;
    uint32_t startTag;
    unsigned executedParameterCount;
    */
   /* 
    struct ParameterTuple {
      int16_t coeff_a;
      int16_t coeff_b;
      int32_t coeff_c;
      uint8_t step;
      uint8_t freq;
      uint8_t shift_a;
      uint8_t shift_b;
      
      uint64_t duration() const;
    };

    unsigned mbx_slot;
    
    // These 3 variables must be kept in sync:
    uint64_t fillLevel;
    unsigned filled; // # of fifo entries currently on LM32    
    std::deque<ParameterTuple> fifo;
    */
   	std::shared_ptr<FunctionGeneratorImpl> fgImpl;      
    
};

}

#endif
