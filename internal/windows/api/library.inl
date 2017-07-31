#pragma once

namespace app {
namespace windows {

    extern "C" {

        int32_t __stdcall FreeLibrary(void*);

        void* __stdcall GetProcAddress(void*,const char*);

        void* __stdcall LoadLibraryA(const char*);

    } // extern "C"

    struct library final {

        struct symbol_t {
            void* const pointer = nullptr;

            symbol_t(void* pointer) : pointer(pointer) {}

            explicit operator bool() const { return pointer != nullptr; }

            template<typename T> operator T*() const { return (T*)pointer; }

            symbol_t operator *() const { return {*(void**)pointer}; }
        };

        void* const pointer = nullptr;

        library() = default;

        library(decltype(nullptr)) : library() {}

        library(const char* path) : pointer(LoadLibraryA(path)) {
            if (not pointer) {
                printf("library \"%s\" not found\n",path);
            }
            //else { printf("library \"%s\" @ %p\n",path,pointer); }
        }

        library(library&& rhs) : pointer(rhs.pointer) { new(&rhs) library(); }

        library& operator =(library&& rhs) {
            if (this != &rhs) { new(this) library(std::move(rhs)); }
            return *this;
        }

        ~library() { if (pointer) { FreeLibrary(pointer); } }

        explicit operator bool() const { return pointer != nullptr; }

        symbol_t operator ()(const char* name) const { return symbol(name); }

        symbol_t constant(const char* name) const { return *symbol(name); }

        symbol_t function(const char* name) const { return symbol(name); }

        symbol_t symbol(const char* name) const {
            symbol_t sym { pointer ? GetProcAddress(pointer,name) : nullptr };
            if (not sym) { printf("symbol \"%s\" not found\n", name); }
            //else { printf("symbol \"%s\" @ %p\n",name,sym.pointer); }
            return sym;
        }

    };

}} // namespace app::windows
