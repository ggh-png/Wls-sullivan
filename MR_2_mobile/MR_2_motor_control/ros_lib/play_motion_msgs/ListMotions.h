#ifndef _ROS_SERVICE_ListMotions_h
#define _ROS_SERVICE_ListMotions_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "play_motion_msgs/MotionInfo.h"

namespace play_motion_msgs
{

static const char LISTMOTIONS[] = "play_motion_msgs/ListMotions";

  class ListMotionsRequest : public ros::Msg
  {
    public:

    ListMotionsRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return LISTMOTIONS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ListMotionsResponse : public ros::Msg
  {
    public:
      uint32_t motions_length;
      typedef play_motion_msgs::MotionInfo _motions_type;
      _motions_type st_motions;
      _motions_type * motions;

    ListMotionsResponse():
      motions_length(0), motions(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->motions_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->motions_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->motions_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->motions_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->motions_length);
      for( uint32_t i = 0; i < motions_length; i++){
      offset += this->motions[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t motions_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      motions_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      motions_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      motions_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->motions_length);
      if(motions_lengthT > motions_length)
        this->motions = (play_motion_msgs::MotionInfo*)realloc(this->motions, motions_lengthT * sizeof(play_motion_msgs::MotionInfo));
      motions_length = motions_lengthT;
      for( uint32_t i = 0; i < motions_length; i++){
      offset += this->st_motions.deserialize(inbuffer + offset);
        memcpy( &(this->motions[i]), &(this->st_motions), sizeof(play_motion_msgs::MotionInfo));
      }
     return offset;
    }

    const char * getType(){ return LISTMOTIONS; };
    const char * getMD5(){ return "151d88e888f918ab21ebda2cef4dd23c"; };

  };

  class ListMotions {
    public:
    typedef ListMotionsRequest Request;
    typedef ListMotionsResponse Response;
  };

}
#endif
