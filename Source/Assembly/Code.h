//
// Created by a_mod on 10.02.2019.
//

#ifndef SIMSYSCOMPILER_CODE_H
#define SIMSYSCOMPILER_CODE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <Types/Type.h>
#include <functional>
#include <General/Stack.h>
#include <memory>
#include <General/ScopedSymbolTable.h>
#include "Fn.h"

#include <Structure/Structure.h>

namespace ACC{
    std::string registerToString(size_t size, Register reg);

    /*! Contains the assembly code generated by the compiler as well as all information required for generating said assembly.
     * */

    class Code {
    private:
        /*! A integer that get iterated every time a new unique id is generated to ensure ids are unique.*/
        size_t uuidCounter = 0;

        /*! A `std::unordered_map` mapping function names to `std::vector`s. These vectors contain `Fn` object with all
         * overloads for a function with the mapped function name.*/
        std::unordered_map<std::string, std::vector<Fn>> fnTable;

        /*! A `std::unordered_map` that maps `Register` to a bool indicating if the Register being mapped is currently in
         * use and shall not be given new data.*/
        std::unordered_map<Register, bool> freeRegisterTable;

        /*! A `ScopedSymbolTable` that contains all `Structure`s, which can be revered to later in the assembly generation
         * (i.e.: Structures stored as variables in the input code)*/
        ScopedSymbolTable<std::shared_ptr<Structure>>* curScope = nullptr;

        /*! The top most scope in the linked list making up the `ScopedSymbolTable` for structures that can be later referred to
         * in the assembly generation. This is used for memory managment.*/
        std::shared_ptr<ScopedSymbolTable<std::shared_ptr<Structure>>> globalScope = nullptr;

        /*! A stack refering to specific function overload, the top of the stack always is the function which has been lastly
         * added to the Assembly Program. It keeps track of a `std::pair` with a `std::string` and `size_t` value, the string
         * refers to the name of the function, as this isn't enough to refer to a specific overload the `size_t` value
         * refers to the index in the vector of overloaded function stored in `Code::fnTable` */
        Stack<std::pair<std::string, size_t>> fnStack;



        std::string dataSection;

    public:
        Code();

        /*! Reserves a assembly register(e.g.: rax, rdi...) such that no other part generating assembly is going to use it until `freeRegister` is called.
         * @param reg The register to reserve.*/
        void reserveRegister(Register reg);

        /*! Allows a assembly register (e.g.: rax, rdi...) to be used again by parts generating assembly.
         * @param reg The register to free.*/
        void freeRegister(Register reg);

        /*! Same as `Code::freeRegister(Register reg)` except it frees all register in vector `regs`.
         * @param regs The vector containing all registers that are supposed to be freed.*/
        void freeRegister(std::vector<Register> regs);

        /*! Returns whether or Not the Register `reg` can be safely  used by Assembly Generation.
         * @return If `reg` is free to be used.*/
        bool isRegisterFree(Register reg);

        /*! Removes the top most function on the `fnStack`.*/
        void popFnFromStack();

        /*! Returns a `Register`, which can be safely used for assembly generation and reserves it.
         * It does this is a specific order: It will return the "highest" register, r15, first. If it isn't free
         * it will return the next lowest register (for instance r14), all the way until rax is returned. This is done
         * as registers like rax sometimes have special purpose and we don't want to reserve it if there are more general
         * registers around.
         * @return A register that can be safely used in assembly generation.*/
        Register getFreeRegister();

        /*! Returns a shared pointer to a Structure which is referred to by the symbol sym. (For instance a variable with
         * name `sym`)
         * @return Returns a `std::shared_ptr<Structure>` referred to by a symbol.*/
        std::shared_ptr<Structure> getVarSymbol(std::string sym);

        /*! Stores a `Structure`  `struc` under symbol `sym`, such that it can later be referenced. This is used for instance
         * for variable generation, where the assembly for the variable is generated and then the `Structure` refering to its location
         * is stored with symbol `sym`.
         * @param sym A `std::string` containg the symbol to store the structure under.
         * @param struc A `std::shared_ptr<Structure>` pointing to the structure to store.
         * @return Returns the newly generated structure.*/
        std::shared_ptr<Structure> emplaceVarSymbol(std::string sym, std::shared_ptr<Structure> struc);

        /*! Returns a vector containing all overloads for a function with name `sym`.
         * @param sym The function symbol to get the overloads of.
         * @return A reference to a `std::vector<Fn>&` object containg all overloads of a function.*/
        std::vector<Fn>& getFnOverloads(std::string sym);

        /*! Gets the last function overload emplaced using `Code::emplaceFnSymbol`. This is used to get the function
         * into which the assembly code being generated should be written, for instance this will return the `Fn` object for
         * the function "_start" in the beginning of Assembly Generation, as that is the function into which to write the
         * assembly at first.
         * @return A `Fn&` referring to the last overload that was emplaced.*/
        Fn& getFnSymbol();

        /*! Creates a new function with symbol `sym`, if the name is already used it adds the function as an overload if it
         * dosen't exist it will create it as a "new" function.
         * @param sym The Symbol of the function being emplaced.
         * @return Returns a object of `Fn&` referring to the just emplaced object.*/
        Fn& emplaceFnSymbol(std::string const & sym);

        /*! Writes a line to the data section of the Assembly.*/
        void writeLineToData(std::string const & str);

        /*! Combines the assembly code of all the functions as-well-as the data section into a string
         * containing valid, assemblable, Assembly.
         * @return The Assembly Code generated.*/
        std::string combineOutput();

        /*! Returns a string that is unique. Unique in all of the string generated by this method, this doesn't guarantee that
         * the string is truly unique.
         * @return A string that is unique.*/
        std::string getUUID();

        /*! Creates a new scope that all symbols emplaced via `emplaceVarSymbol` will be stored under. Called for instance
         * when starting to generate the Assembly for a new function.*/
        void pushScope();

        /*! Removes one scope such that the previous scope is the one symbols emplaced via `emplaceVarSymbol` are stored under.
         * Called, for instance, when we are done with generating the code for a loop.*/
        void popScope();
    };
}

#endif //SIMSYSCOMPILER_CODE_H
