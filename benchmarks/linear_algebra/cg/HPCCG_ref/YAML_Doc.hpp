
//@HEADER
// ************************************************************************
// 
//               HPCCG: Simple Conjugate Gradient Benchmark Code
//                 Copyright (2006) Sandia Corporation
// 
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
// 
// BSD 3-Clause License
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// 
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Questions? Contact Michael A. Heroux (maherou@sandia.gov) 
// 
// ************************************************************************
//@HEADER
// Changelog
//
// Version 0.1
// - Initial version.
//
/////////////////////////////////////////////////////////////////////////

#ifndef YAML_DOC_H
#define YAML_DOC_H
#include <string>
#include <vector>
#include "YAML_Element.hpp"

//! The Mantevo YAML_Doc class for the uniform collecting and reporting of performance data for mini-applications

/*!

The YAML_Doc class works in conjuction with the YAML_Element class to facilitate easy collecting and reporting of YAML-formatted
data that can be then registered with the Mantevo results collection website.

\code

//EXAMPLE CODE FOR GENERATING YAML

  YAML_Doc doc("hpccg","1.0");
  doc.add("final_residual",1.4523e-13);
  doc.add("time","4.893"); 
 
//note: the following line will remove the data (4.890) associated with "time"
  doc.get("time")->add("total",4.243);

//note:  the following line will likewise remove the data (1.243) associated with "time"
  doc.get("time")->get("total")->add("time",2.457);
  doc.get("time")->get("total")->add("flops",4.88e5);
  doc.get("time")->add("ddot",1.243);
  doc.get("time")->add("sparsemv","");
  doc.get("time")->get("sparsemv")->add("time",0.3445);
  doc.get("time")->get("sparsemv")->add("overhead","");
  doc.get("time")->get("sparsemv")->get("overhead")->add("time",0.0123);
  doc.get("time")->get("sparsemv")->get("overhead")->add("percentage",0.034);
  cout << doc.generateYAML() << endl; 
  return 0;

\endcode

Below is the output generated by the above code:

\verbatim

final_residual: 1.4523e-13
time: 
  total:
    time: 2.457
    flops: 4.88e5
  ddot: 1.243
  sparsemv:
    time: 0.3445
    overhead:
      time: 0.0123
      percentage: 0.034

\endverbatim

\note {No value is allowed to be attached to a key that has children.  If children are added to a key, the value is simply set to "".}

*/
class YAML_Doc: public YAML_Element {
  public:
  //! Constructor: accepts mini-application name and version as strings, optionally accepts directory and file name for printing results.
  /*!
    The sole constructor for this class accepts and name and version number for the mini-application as well as optional directory 
    and file name information for results that are generated by the generateYAML() method.
    \param miniApp_Name (in) string containing name of the mini-application
    \param miniApp_Version (in) string containing the version of the mini-application
    \param destination_Directory (in, optional) path of diretory where results file will be stored, relative to current working directory. 
           If this value is not supplied, the results file will be stored in the current working directory.  If the directory does not exist
	   it will be created.
    \param destination_FileName (in, optional) root name of the results file.  A suffix of ".yaml" will be automatically appended.  If no
           file name is specified the filename will be constructed by concatenating the miniAppName + miniAppVersion + ".yaml" strings.
  */
  YAML_Doc(const std::string& miniApp_Name, const std::string& miniApp_Version, const std::string& destination_Directory = "", const std::string& destination_FileName = "");
  //! Destructor
  ~YAML_Doc();
  //! Generate YAML results to standard out and to a file using specified directory and filename, using current directory and miniAppName + miniAppVersion + ".yaml" by default
  std::string generateYAML();

protected:
  std::string miniAppName;
  std::string miniAppVersion;
  std::string destinationDirectory;
  std::string destinationFileName;
};
#endif /* YAML_DOC_H */
