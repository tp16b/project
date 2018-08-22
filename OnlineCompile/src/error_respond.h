#pragma once
#include "http.h"

int send_error_page(int sock, const char* path, int error_code);

int echo_error(int sock, int error_code); 


