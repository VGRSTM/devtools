/*
 * Copyright (c) 2020-2021 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PROJMGRPARSER_H
#define PROJMGRPARSER_H

#include <map>
#include <string>
#include <vector>

/**
* @brief type pair containing
*        build-type,
*        target-type
*/
struct TypePair {
  std::string build;
  std::string target;
};

/**
 * @brief include/exclude types
 *        for-type (include)
 *        not-for-type (exclude)
*/
struct TypeFilter {
  std::vector<TypePair> include;
  std::vector<TypePair> exclude;
};

/**
 * @brief compiler misc controls
 *        compiler name (to be deprecated)
 *        for compiler control,
 *        options for assembler,
 *        options for c compiler,
 *        options for c++ compiler,
 *        options for c and c++ compiler,
 *        options for linker,
 *        options for linker c flags,
 *        options for linker c++ flags,
 *        options for archiver
*/
struct MiscItem {
  std::string compiler;
  std::string forCompiler;
  std::vector<std::string> as;
  std::vector<std::string> c;
  std::vector<std::string> cpp;
  std::vector<std::string> c_cpp;
  std::vector<std::string> link;
  std::vector<std::string> link_c;
  std::vector<std::string> link_cpp;
  std::vector<std::string> lib;
  std::vector<std::string> library;
};

/**
 * @brief pack item containing
 *        pack name
 *        pack path
 *        type filter
*/
struct PackItem {
  std::string pack;
  std::string path;
  TypeFilter type;
};

/**
 * @brief processor item containing
 *        processor fpu,
 *        processor trustzone,
 *        processor endianess
*/
struct ProcessorItem {
  std::string fpu;
  std::string trustzone;
  std::string endian;
};

/**
 * @brief build types containing
 *        toolchain,
 *        optimization level,
 *        debug information,
 *        preprocessor defines,
 *        preprocessor undefines,
 *        include paths,
 *        exclude paths,
 *        misc compiler controls,
 *        platform processor
*/
struct BuildType {
  std::string compiler;
  std::string optimize;
  std::string debug;
  std::string warnings;
  std::vector<std::string> defines;
  std::vector<std::string> undefines;
  std::vector<std::string> addpaths;
  std::vector<std::string> delpaths;
  std::vector<MiscItem> misc;
  ProcessorItem processor;
  std::vector<std::pair<std::string, std::string>> variables;
};

/**
 * @brief target types containing
 *        platform board,
 *        platform device,
*/
struct TargetType {
  std::string board;
  std::string device;
  BuildType build;
};

/**
 * @brief rte directory item containing
 *        rte directory path,
 *        type inclusion
*/
struct RteDirItem {
  std::string dir;
  TypeFilter type;
};

/**
 * @brief directories item containing
 *        intdir directory,
 *        outdir directory,
 *        cprj directory,
 *        rte directory,
*/
struct DirectoriesItem {
  std::string gendir;
  std::string intdir;
  std::string outdir;
  std::string cprj;
  std::string rte;
};

/**
 * @brief component item containing
 *        component identifier,
 *        component build settings,
 *        type inclusion
*/
struct ComponentItem {
  std::string component;
  std::string condition;
  std::string fromPack;
  BuildType build;
  TypeFilter type;
};

/**
 * @brief output item containing
 *        type [elf, hex, bin, lib],
 *        filename,
 *        context inclusion
*/
struct OutputItem {
  std::string type;
  std::string file;
  TypeFilter typeFilter;
};

/**
 * @brief layer item containing
 *        layer name,
 *        layer type,
 *        layer build settings,
 *        type inclusion
*/
struct LayerItem {
  std::string layer;
  std::string type;
  BuildType build;
  TypeFilter typeFilter;
};

/**
 * @brief connect item containing
 *        connect functionality description
 *        set <config-id>.<select> value for config option identification
 *        info display description
 *        vector of provided connections pairs,
 *        vector of consumed connections pairs
*/
struct ConnectItem {
  std::string connect;
  std::string set;
  std::string info;
  std::vector<std::pair<std::string, std::string>> provides;
  std::vector<std::pair<std::string, std::string>> consumes;
};

/**
 * @brief linker item containing
 *        regions file,
 *        script file,
 *        preprocessor defines,
 *        for compiler control,
 *        type inclusion
*/
struct LinkerItem {
  std::string regions;
  std::string script;
  std::vector<std::string> defines;
  std::vector<std::string> forCompiler;
  TypeFilter typeFilter;
};

/**
 * @brief setup item containing
 *        setup description name,
 *        for compiler control,
 *        setup build settings,
 *        type inclusion
*/
struct SetupItem {
  std::string description;
  std::vector<std::string> forCompiler;
  BuildType build;
  TypeFilter type;
};

/**
 * @brief file node containing
 *        file path,
 *        for compiler control,
 *        file category,
 *        file build settings,
 *        type filter
*/
struct FileNode {
  std::string file;
  std::vector<std::string> forCompiler;
  std::string category;
  BuildType build;
  TypeFilter type;
};

/**
 * @brief group node containing
 *        group name,
 *        for compiler control,
 *        children files,
 *        children groups,
 *        group build settings,
 *        type filter
*/
struct GroupNode {
  std::string group;
  std::vector<std::string> forCompiler;
  std::vector<FileNode> files;
  std::vector<GroupNode> groups;
  BuildType build;
  TypeFilter type;
};

/**
 * @brief context descriptor containing
 *        cproject filename,
 *        type filter
*/
struct ContextDesc {
  std::string cproject;
  TypeFilter type;
};

/**
 * @brief default item containing
 *        cdefault path
 *        build types,
 *        compiler,
 *        list of packs
*/
struct CdefaultItem {
  std::string path;
  std::map<std::string, BuildType> buildTypes;
  std::string compiler;
  std::vector<PackItem> packs;
  std::vector<MiscItem> misc;
};

/**
 * @brief solution item containing
 *        csolution name,
 *        csolution path,
 *        csolution directory,
 *        output directories,
 *        build types,
 *        target types,
 *        target properties,
 *        list of cprojects,
 *        list of contexts descriptors,
 *        list of packs
*/
struct CsolutionItem {
  std::string name;
  std::string path;
  std::string directory;
  DirectoriesItem directories;
  std::map<std::string, BuildType> buildTypes;
  std::map<std::string, TargetType> targetTypes;
  TargetType target;
  std::vector<std::string> cprojects;
  std::vector<ContextDesc> contexts;
  std::vector<PackItem> packs;
};

/**
 * @brief cproject item containing
 *        project name,
 *        project path,
 *        project directory,
 *        project output type,
 *        project target properties,
 *        list of required components,
 *        list of user groups,
 *        list of layers,
 *        list of setups,
 *        list of connections
 *        list of packs
*/
struct CprojectItem {
  std::string name;
  std::string path;
  std::string directory;
  std::string outputType;
  TargetType target;
  std::vector<RteDirItem> rteDirs;
  std::vector<ComponentItem> components;
  std::vector<GroupNode> groups;
  std::vector<LayerItem> clayers;
  std::vector<SetupItem> setups;
  std::vector<ConnectItem> connections;
  std::vector<PackItem> packs;
  std::vector<OutputItem> outputFiles;
  std::vector<LinkerItem> linker;
};

/**
 * @brief clayer item containing
 *        layer name,
 *        layer path,
 *        layer type,
 *        layer directory,
 *        layer output type,
 *        layer target properties,
 *        list of required components,
 *        list of user groups,
 *        list of connections
 *        list of packs
*/
struct ClayerItem {
  std::string name;
  std::string path;
  std::string type;
  std::string directory;
  std::string outputType;
  TargetType target;
  std::vector<RteDirItem> rteDirs;
  std::vector<ComponentItem> components;
  std::vector<GroupNode> groups;
  std::vector<ConnectItem> connections;
  std::vector<PackItem> packs;
  std::vector<LinkerItem> linker;
  std::string forBoard;
  std::string forDevice;
};

/**
 * @brief projmgr parser class for public interfacing
*/
class ProjMgrParser {
public:
  /**
   * @brief class constructor
  */
  ProjMgrParser(void);

  /**
   * @brief class destructor
  */
  ~ProjMgrParser(void);

  /**
   * @brief parse cdefault
   * @param input cdefault.yml file
  */
  bool ParseCdefault(const std::string& input, bool checkSchema);

  /**
   * @brief parse cproject
   * @param input cproject.yml file
   * @param boolean parse single project, default false
  */
  bool ParseCproject(const std::string& input, bool checkSchema, bool single = false);

  /**
   * @brief parse csolution
   * @param input csolution.yml file
  */
  bool ParseCsolution(const std::string& input, bool checkSchema);

  /**
   * @brief parse clayer
   * @param input clayer.yml file
  */
  bool ParseClayer(const std::string& input, bool checkSchema);

  /**
   * @brief parse generic clayer files
   * @param input clayer.yml file
  */
  bool ParseGenericClayer(const std::string& input, bool checkSchema);

  /**
   * @brief get cdefault
   * @return cdefault item
  */
  CdefaultItem& GetCdefault(void);

  /**
   * @brief get csolution
   * @return csolution item
  */
  CsolutionItem& GetCsolution(void);

  /**
   * @brief get cprojects
   * @return cprojects map
  */
  std::map<std::string, CprojectItem>& GetCprojects(void);

  /**
   * @brief get clayers
   * @return clayers map
  */
  std::map<std::string, ClayerItem>& GetClayers(void);

  /**
   * @brief get generic clayers
   * @return clayers map
  */
  std::map<std::string, ClayerItem>& GetGenericClayers(void);

protected:
  CdefaultItem m_cdefault;
  CsolutionItem m_csolution;
  std::map<std::string, CprojectItem> m_cprojects;
  std::map<std::string, ClayerItem> m_clayers;
  std::map<std::string, ClayerItem> m_genericClayers;
};

#endif  // PROJMGRPARSER_H
