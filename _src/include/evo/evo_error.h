//
// Created by Ciaran on 09/09/2020.
//

#ifndef EVOGYM_EVO_ERROR_H
#define EVOGYM_EVO_ERROR_H


#include <iostream>
#include <stdexcept>
#include <string>

/*
 * This error module was shamelessly stolen from NumCpp
 */

namespace evo {

#define THROW_HELPER(ex_type)                                       \
    for (std::stringstream ss; true; throwError<ex_type>(__FILE__, __func__, __LINE__, ss.str())) \
        ss

    using FileNotFoundError = std::logic_error;
    using NotImplementedError = std::logic_error;


    /**
     * @brief Makes the full error message string
     * @param file: the file
     * @param function: the function
     * @param line: the line of the file
     * @param msg: the message to throw (default "")
     */
    template<typename ErrorType>
    void throwError(const std::string &file,
                    const std::string &function,
                    unsigned int line,
                    const std::string &msg = "") {
        std::ostringstream errMsg;
        errMsg << file << ":" << line << ":" << function << ":"
               << "\nError: " << msg << std::endl;
        std::cerr << errMsg.str();
        throw ErrorType(errMsg.str());
    }


#define INVALID_ARGUMENT_ERROR          THROW_HELPER(std::invalid_argument)
#define LOGIC_ERROR                     THROW_HELPER(std::logic_error)
#define RUNTIME_ERROR                   THROW_HELPER(std::runtime_error)
#define NOT_IMPLEMENTED_ERROR           THROW_HELPER(NotImplementedError)
#define FILE_NOT_FOUND_ERROR            THROW_HELPER(FileNotFoundError)

}// namespace evo

#endif//EVOGYM_EVO_ERROR_H
