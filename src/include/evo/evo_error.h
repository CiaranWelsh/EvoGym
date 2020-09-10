//
// Created by Ciaran on 09/09/2020.
//

#ifndef EVOGYM_EVO_ERROR_H
#define EVOGYM_EVO_ERROR_H


#define THROW_INVALID_ARGUMENT_ERROR(msg) nc::error::throwError<std::invalid_argument>(__FILE__, __func__, __LINE__, msg)
#define THROW_RUNTIME_ERROR(msg) nc::error::throwError<std::runtime_error>(__FILE__, __func__, __LINE__, msg)


#endif //EVOGYM_EVO_ERROR_H
