#pragma once

#define CYDL_MAJOR_VERSION 0
#define CYDL_MINOR_VERSION 1
#define CYDL_PATCH_VERSION 0


#define CYDL_VERSION_AT_LEAST(x,y,z) (CYDL_MAJOR_VERSION>x || (CYDL_MAJOR_VERSION>=x && \
                                      (CYDL_MINOR_VERSION>y || (CYDL_MINOR_VERSION>=y && \
                                                                 CYDL_PATCH_VERSION>=z))))