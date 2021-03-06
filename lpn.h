
#ifndef _LPN_H_
#define _LPN_H_

#include <assert.h>
#include <vector>
#include "msg_def.h"


class lpn_t
{
private:
    string name;
    
    config_t init_cfg;
    uint32_t index;
    config_t end_cfg;
    uint16_t tag;
public:
    
    std::vector<message_t> msg_vector;
    lpn_t() {}
    void set_tag(uint16_t x){
        tag=x;
    }
    uint16_t get_tag(){
        return tag;
    }
    config_t get_end_cfg(){
        return end_cfg;
    }
    void set_end_cfg(config_t x){
        end_cfg=x;
    }
    void set_flow_name(const string& n) {
        name = n;
    }
    
    string get_flow_name() {
        return name;
    }
    
    void insert_msg(const message_t& msg) {
        msg_vector.push_back(msg);
        init_cfg = null_cfg;
    }
    
    void set_init_cfg(const config_t c) {
        init_cfg = c;
    }
    
    
    void set_index(uint32_t idx) {
        index = idx;
    }
    
    uint32_t get_index() {
        return index;
    }
    
    config_t accept(const message_t& other) const {
        
            const message_t& msg = msg_vector.at(0);
        if (msg.src == other.src && msg.dest == other.dest && (msg.cmd == other.cmd ||other.cmd==0)&& ((init_cfg & msg.pre_cfg) == msg.pre_cfg)){
            
                return msg.post_cfg;
        }
                return null_cfg;
    }

    
    message_t accept(const message_t& other, const config_t& cfg) const {
        for (unsigned i=0; i<msg_vector.size(); i++) {
            const message_t& msg = msg_vector.at(i);
 
            if (msg.src == other.src && msg.dest == other.dest && (msg.cmd == other.cmd || other.cmd==0)  && ((cfg & msg.pre_cfg) == msg.pre_cfg)) {
                //if ((cfg & ~msg.pre_cfg & msg.post_cfg) != 0) {
//                    //cout << bitset<12>(cfg) << endl
//                        << bitset<12>(msg.pre_cfg) << endl
//                    << bitset<12>(msg.post_cfg) << endl;
//                    //assert(false);
                 //   return 0;
                //}
               
               // return (cfg & ~msg.pre_cfg) | msg.post_cfg;
                return msg;
            }
        }
        message_t null_msg;
        null_msg.post_cfg=null_cfg;
        return null_msg;
    }
};


#endif

