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



#define INVALID_ARGUMENT_ERROR(msg) throwError<std::invalid_argument>(__FILE__, __func__, __LINE__, msg)
#define RUNTIME_ERROR(msg) throwError<std::runtime_error>(__FILE__, __func__, __LINE__, msg)
#define LOGIC_ERROR(msg) throwError<std::logic_error>(__FILE__, __func__, __LINE__, msg)

    class NotImplementedError : public std::logic_error {};
#define NOT_IMPLEMENTED_ERROR(msg) throwError<std::logic_error>(__FILE__, __func__, __LINE__, msg)


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


}// namespace evo

#endif//EVOGYM_EVO_ERROR_H
