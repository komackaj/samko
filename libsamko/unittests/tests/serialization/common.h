#ifndef SAMKO_SERIALIZATIONTEST_COMMON_H_INCLUDED
#define SAMKO_SERIALIZATIONTEST_COMMON_H_INCLUDED

#include <gtest/gtest.h>
#include <mocks/serialization/mockserializable.h>

void dataEquals(MockSerializable::Data expected, MockSerializable::Data actual);
#endif // SAMKO_SERIALIZATIONTEST_COMMON_H_INCLUDED
