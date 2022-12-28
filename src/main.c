#include "shell.h"

int main(int argc, char** argv) {
    int error_code = shell_run();
     
    print_error_message(error_code); 
    return error_code;
}