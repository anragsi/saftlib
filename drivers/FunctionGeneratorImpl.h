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
#ifndef FUNCTION_GENERATOR_IMPL_H
#define FUNCTION_GENERATOR_IMPL_H

#include <deque>

namespace saftlib {

class TimingReceiver;

class FunctionGeneratorChannelAllocation //: public Glib::Object
{
  public:
    std::vector<int> indexes;
};

class FunctionGeneratorImpl //: public Glib::Object
{
	friend class MasterFunctionGenerator;
	
  public:
//    typedef FunctionGenerator_Service ServiceType;
    struct ConstructorType {
      std::string objectPath;
      TimingReceiver* dev;
      std::shared_ptr<FunctionGeneratorChannelAllocation> allocation;
      eb_address_t fgb;
      eb_address_t swi;
      etherbone::sdb_msi_device base;
      sdb_device mbx;
      unsigned num_channels;
      unsigned buffer_size;
      unsigned int index;
      uint32_t macro;
    };
    FunctionGeneratorImpl(const ConstructorType& args);
    ~FunctionGeneratorImpl();
    
    //static std::shared_ptr<FunctionGenerator> create(const ConstructorType& args);
    


    void Arm();
    void Abort();
    uint64_t ReadFillLevel();
    bool appendParameterSet(const std::vector< int16_t >& coeff_a, const std::vector< int16_t >& coeff_b, const std::vector< int32_t >& coeff_c, const std::vector< unsigned char >& step, const std::vector< unsigned char >& freq, const std::vector< unsigned char >& shift_a, const std::vector< unsigned char >& shift_b);
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

    std::string GetName();

    sigc::signal<void, bool> signal_enabled;
    sigc::signal<void, bool> signal_running;
    sigc::signal<void, bool> signal_armed;
    sigc::signal<void> signal_refill;
    sigc::signal<void, uint64_t> signal_started;
    sigc::signal<void, uint64_t, bool, bool, bool> signal_stopped;

    void flush();
    void arm();
    void Reset();
    
    
    
  protected:
    bool lowFill() const;
    void irq_handler(eb_data_t msi);
    void refill();
    void releaseChannel();
    void acquireChannel();

    bool ResetFailed();
    void ownerQuit();

            
            
            
    TimingReceiver* dev;
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
    eb_address_t mailbox_slot_address;
    
    // These 3 variables must be kept in sync:
    uint64_t fillLevel;
    unsigned filled; // # of fifo entries currently on LM32
    std::deque<ParameterTuple> fifo;
};

}

#endif
