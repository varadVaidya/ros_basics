// Generated by gencpp from file ros_basics/addTwoInts.msg
// DO NOT EDIT!


#ifndef ROS_BASICS_MESSAGE_ADDTWOINTS_H
#define ROS_BASICS_MESSAGE_ADDTWOINTS_H

#include <ros/service_traits.h>


#include <ros_basics/addTwoIntsRequest.h>
#include <ros_basics/addTwoIntsResponse.h>


namespace ros_basics
{

struct addTwoInts
{

typedef addTwoIntsRequest Request;
typedef addTwoIntsResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct addTwoInts
} // namespace ros_basics


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::ros_basics::addTwoInts > {
  static const char* value()
  {
    return "6a2e34150c00229791cc89ff309fff21";
  }

  static const char* value(const ::ros_basics::addTwoInts&) { return value(); }
};

template<>
struct DataType< ::ros_basics::addTwoInts > {
  static const char* value()
  {
    return "ros_basics/addTwoInts";
  }

  static const char* value(const ::ros_basics::addTwoInts&) { return value(); }
};


// service_traits::MD5Sum< ::ros_basics::addTwoIntsRequest> should match
// service_traits::MD5Sum< ::ros_basics::addTwoInts >
template<>
struct MD5Sum< ::ros_basics::addTwoIntsRequest>
{
  static const char* value()
  {
    return MD5Sum< ::ros_basics::addTwoInts >::value();
  }
  static const char* value(const ::ros_basics::addTwoIntsRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::ros_basics::addTwoIntsRequest> should match
// service_traits::DataType< ::ros_basics::addTwoInts >
template<>
struct DataType< ::ros_basics::addTwoIntsRequest>
{
  static const char* value()
  {
    return DataType< ::ros_basics::addTwoInts >::value();
  }
  static const char* value(const ::ros_basics::addTwoIntsRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::ros_basics::addTwoIntsResponse> should match
// service_traits::MD5Sum< ::ros_basics::addTwoInts >
template<>
struct MD5Sum< ::ros_basics::addTwoIntsResponse>
{
  static const char* value()
  {
    return MD5Sum< ::ros_basics::addTwoInts >::value();
  }
  static const char* value(const ::ros_basics::addTwoIntsResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::ros_basics::addTwoIntsResponse> should match
// service_traits::DataType< ::ros_basics::addTwoInts >
template<>
struct DataType< ::ros_basics::addTwoIntsResponse>
{
  static const char* value()
  {
    return DataType< ::ros_basics::addTwoInts >::value();
  }
  static const char* value(const ::ros_basics::addTwoIntsResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // ROS_BASICS_MESSAGE_ADDTWOINTS_H
