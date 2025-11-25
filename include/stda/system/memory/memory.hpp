#include <stda/numbers/numbers.hpp>
#if _WIN32
#include <windows.h>
#include <Psapi.h>
#include <iostream>
#else
#include <sys/resources.h>
#endif

#ifndef STDXMEMORY
#define STDXMEMORY

/* @Documentacion:
 * Este archivo contiene funciones para ver la memoria del sistema o de una direccion
 */

/// @brief Espacio para todas las funciones
namespace memory
{
    /// @brief Clse que contiene las funciones para visualizar la memoria del programa
    class process_memory_counters : private _PROCESS_MEMORY_COUNTERS
    {
    public:
        /// @brief Cobstructor por defecto
        process_memory_counters()
        {
            if (!GetProcessMemoryInfo(GetCurrentProcess(), (_PROCESS_MEMORY_COUNTERS*)this, sizeof(_PROCESS_MEMORY_COUNTERS)))
                throw std::runtime_error("Error al acceder a la memoria del sistema.");
        }
        /// @brief Obtiene el maximo de memoria de trabajo
        /// @return Devuleve un (?size_t?) en bytes
        size_t get_peak_memory_working();
        /// @brief Obtiene el numero de paginas fallidas
        /// @return Devuleve un (?size_t?) de ese numero
        size_t get_page_fault_count();
        /// @brief Obtiene el numero de paginas en uso
        /// @return Devuleve un (?size_t?) de ese numero
        size_t get_page_file_usage();
        /// @brief Obtiene el numero maximo de paginas en uso
        /// @return Devuleve un (?size_t?) de ese numero
        size_t get_page_file_peak_usage();
        /// @brief Proximamente...
        /// @return Devuleve un (?size_t?) de ese numero
        size_t get_quota_non_paged_pool_usage();
        /// @brief Proximamente...
        /// @return Devuleve un (?size_t?) de ese numero
        size_t get_quota_paged_pool_usage();
        /// @brief Proximamente...
        /// @return Devuleve un (?size_t?) de ese numero
        size_t get_quota_peak_non_paged_pool_usage();
        /// @brief Proximamente...
        /// @return Devuleve un (?size_t?) de ese numero
        size_t get_quota_peak_paged_pool_usage();
        /// @brief Proximamente...
        /// @return Devuleve un (?size_t?) de ese numero
        size_t get_working_set_size();
        /// @brief Proximamente...
        /// @return Devuleve un (?size_t?) de ese numero
        int get_cb() {return this->cb;}
        process_memory_counters operator+(const process_memory_counters& __other)
        {
            process_memory_counters resut;
            resut.PageFaultCount = this->PageFaultCount + __other.PageFaultCount;
            resut.PagefileUsage = this->PagefileUsage + __other.PagefileUsage;
            resut.PeakPagefileUsage = this->PeakPagefileUsage + __other.PeakPagefileUsage;
            resut.PeakWorkingSetSize = this->PeakWorkingSetSize + __other.PeakWorkingSetSize;
            resut.QuotaNonPagedPoolUsage = this->QuotaNonPagedPoolUsage + __other.QuotaNonPagedPoolUsage;
            resut.QuotaPagedPoolUsage = this->QuotaPagedPoolUsage + __other.QuotaPagedPoolUsage;
            resut.QuotaPeakNonPagedPoolUsage = this->QuotaPeakNonPagedPoolUsage + __other.QuotaPeakNonPagedPoolUsage;
            resut.QuotaPeakPagedPoolUsage = this->QuotaPeakPagedPoolUsage + __other.QuotaPeakPagedPoolUsage;
            resut.WorkingSetSize = this->WorkingSetSize + __other.WorkingSetSize;
            resut.cb = this->cb + __other.cb;
            return resut;
        }
        process_memory_counters operator-(const process_memory_counters& __other)
        {
            process_memory_counters resut;
            resut.PageFaultCount = this->PageFaultCount - __other.PageFaultCount;
            resut.PagefileUsage = this->PagefileUsage - __other.PagefileUsage;
            resut.PeakPagefileUsage = this->PeakPagefileUsage - __other.PeakPagefileUsage;
            resut.PeakWorkingSetSize = this->PeakWorkingSetSize - __other.PeakWorkingSetSize;
            resut.QuotaNonPagedPoolUsage = this->QuotaNonPagedPoolUsage - __other.QuotaNonPagedPoolUsage;
            resut.QuotaPagedPoolUsage = this->QuotaPagedPoolUsage - __other.QuotaPagedPoolUsage;
            resut.QuotaPeakNonPagedPoolUsage = this->QuotaPeakNonPagedPoolUsage - __other.QuotaPeakNonPagedPoolUsage;
            resut.QuotaPeakPagedPoolUsage = this->QuotaPeakPagedPoolUsage - __other.QuotaPeakPagedPoolUsage;
            resut.WorkingSetSize = this->WorkingSetSize - __other.WorkingSetSize;
            resut.cb = this->cb - __other.cb;
            return resut;
        }
    };
    /// @brief Permite visualizar en base a bytes un espacio de memoria al que se pueda acceder
    /// @param ptr Direccion de memoria a visualizar
    /// @param size Numero de datos a visualizar(!Atencion: Debe de tener cuidado ya que un tamano equivocado puede causar problemas con la memoria!)
    void vmemory(const void *ptr, size_t size);
}

#endif