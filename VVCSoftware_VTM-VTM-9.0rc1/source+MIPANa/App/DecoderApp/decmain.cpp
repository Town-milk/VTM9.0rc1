/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2020, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     decmain.cpp
    \brief    Decoder application main
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "DecApp.h"
#include "program_options_lite.h"

//! \ingroup DecoderApp
//! \{

// ====================================================================================================================
// Main function
// ====================================================================================================================

int main(int argc, char* argv[])
{
  int returnCode = EXIT_SUCCESS;

  // print information
  fprintf( stdout, "\n" );
  fprintf( stdout, "VVCSoftware: VTM Decoder Version %s ", VTM_VERSION );
  fprintf( stdout, NVM_ONOS );
  fprintf( stdout, NVM_COMPILEDBY );
  fprintf( stdout, NVM_BITS );
#if ENABLE_SIMD_OPT
  std::string SIMD;
  df::program_options_lite::Options optsSimd;
  optsSimd.addOptions()( "SIMD", SIMD, string( "" ), "" );
  df::program_options_lite::SilentReporter err;
  df::program_options_lite::scanArgv( optsSimd, argc, ( const char** ) argv, err );
  fprintf( stdout, "[SIMD=%s] ", read_x86_extension( SIMD ) );
#endif
#if ENABLE_TRACING
  fprintf( stdout, "[ENABLE_TRACING] " );
#endif
  fprintf( stdout, "\n" );

  DecApp *pcDecApp = new DecApp;
  // parse configuration
  if(!pcDecApp->parseCfg( argc, argv ))
  {
    returnCode = EXIT_FAILURE;
    return returnCode;
  }

  // starting time
  double dResult;
  clock_t lBefore = clock();

  // call decoding function
#ifndef _DEBUG
  try
  {
#endif // !_DEBUG
    if( 0 != pcDecApp->decode() )
    {
      printf( "\n\n***ERROR*** A decoding mismatch occured: signalled md5sum does not match\n" );
      returnCode = EXIT_FAILURE;
    }
#ifndef _DEBUG
  }
  catch( Exception &e )
  {
    std::cerr << e.what() << std::endl;
    returnCode = EXIT_FAILURE;
  }
  catch (const std::bad_alloc &e)
  {
    std::cout << "Memory allocation failed: " << e.what() << std::endl;
    returnCode = EXIT_FAILURE;
  }
#endif

#if LTS_MIP_ANAYTSIS

  FILE *OutFile = fopen(g_logFileName, "w");
  
  fprintf(OutFile, "64x64:\t");
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose0_64x64, g_mipflag1_mipmodeidx1_transpose0_64x64,
          g_mipflag1_mipmodeidx2_transpose0_64x64, g_mipflag1_mipmodeidx3_transpose0_64x64,
          g_mipflag1_mipmodeidx4_transpose0_64x64, g_mipflag1_mipmodeidx5_transpose0_64x64,
          g_mipflag1_mipmodeidx6_transpose0_64x64, g_mipflag1_mipmodeidx7_transpose0_64x64,
          g_mipflag1_mipmodeidx8_transpose0_64x64, g_mipflag1_mipmodeidx9_transpose0_64x64,
          g_mipflag1_mipmodeidx10_transpose0_64x64, g_mipflag1_mipmodeidx11_transpose0_64x64,
          g_mipflag1_mipmodeidx12_transpose0_64x64, g_mipflag1_mipmodeidx13_transpose0_64x64,
          g_mipflag1_mipmodeidx14_transpose0_64x64, g_mipflag1_mipmodeidx15_transpose0_64x64);
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose1_64x64, g_mipflag1_mipmodeidx1_transpose1_64x64,
          g_mipflag1_mipmodeidx2_transpose1_64x64, g_mipflag1_mipmodeidx3_transpose1_64x64,
          g_mipflag1_mipmodeidx4_transpose1_64x64, g_mipflag1_mipmodeidx5_transpose1_64x64,
          g_mipflag1_mipmodeidx6_transpose1_64x64, g_mipflag1_mipmodeidx7_transpose1_64x64,
          g_mipflag1_mipmodeidx8_transpose1_64x64, g_mipflag1_mipmodeidx9_transpose1_64x64,
          g_mipflag1_mipmodeidx10_transpose1_64x64, g_mipflag1_mipmodeidx11_transpose1_64x64,
          g_mipflag1_mipmodeidx12_transpose1_64x64, g_mipflag1_mipmodeidx13_transpose1_64x64,
          g_mipflag1_mipmodeidx14_transpose1_64x64, g_mipflag1_mipmodeidx15_transpose1_64x64);
  fprintf(OutFile, "%d\n", g_Intra_64x64);

  fprintf(OutFile, "32x32:\t");
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose0_32x32, g_mipflag1_mipmodeidx1_transpose0_32x32,
          g_mipflag1_mipmodeidx2_transpose0_32x32, g_mipflag1_mipmodeidx3_transpose0_32x32,
          g_mipflag1_mipmodeidx4_transpose0_32x32, g_mipflag1_mipmodeidx5_transpose0_32x32,
          g_mipflag1_mipmodeidx6_transpose0_32x32, g_mipflag1_mipmodeidx7_transpose0_32x32,
          g_mipflag1_mipmodeidx8_transpose0_32x32, g_mipflag1_mipmodeidx9_transpose0_32x32,
          g_mipflag1_mipmodeidx10_transpose0_32x32, g_mipflag1_mipmodeidx11_transpose0_32x32,
          g_mipflag1_mipmodeidx12_transpose0_32x32, g_mipflag1_mipmodeidx13_transpose0_32x32,
          g_mipflag1_mipmodeidx14_transpose0_32x32, g_mipflag1_mipmodeidx15_transpose0_32x32);
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose1_32x32, g_mipflag1_mipmodeidx1_transpose1_32x32,
          g_mipflag1_mipmodeidx2_transpose1_32x32, g_mipflag1_mipmodeidx3_transpose1_32x32,
          g_mipflag1_mipmodeidx4_transpose1_32x32, g_mipflag1_mipmodeidx5_transpose1_32x32,
          g_mipflag1_mipmodeidx6_transpose1_32x32, g_mipflag1_mipmodeidx7_transpose1_32x32,
          g_mipflag1_mipmodeidx8_transpose1_32x32, g_mipflag1_mipmodeidx9_transpose1_32x32,
          g_mipflag1_mipmodeidx10_transpose1_32x32, g_mipflag1_mipmodeidx11_transpose1_32x32,
          g_mipflag1_mipmodeidx12_transpose1_32x32, g_mipflag1_mipmodeidx13_transpose1_32x32,
          g_mipflag1_mipmodeidx14_transpose1_32x32, g_mipflag1_mipmodeidx15_transpose1_32x32);
  fprintf(OutFile, "%d\n", g_Intra_32x32);

  fprintf(OutFile, "32x16:\t");
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose0_32x16, g_mipflag1_mipmodeidx1_transpose0_32x16,
          g_mipflag1_mipmodeidx2_transpose0_32x16, g_mipflag1_mipmodeidx3_transpose0_32x16,
          g_mipflag1_mipmodeidx4_transpose0_32x16, g_mipflag1_mipmodeidx5_transpose0_32x16,
          g_mipflag1_mipmodeidx6_transpose0_32x16, g_mipflag1_mipmodeidx7_transpose0_32x16,
          g_mipflag1_mipmodeidx8_transpose0_32x16, g_mipflag1_mipmodeidx9_transpose0_32x16,
          g_mipflag1_mipmodeidx10_transpose0_32x16, g_mipflag1_mipmodeidx11_transpose0_32x16,
          g_mipflag1_mipmodeidx12_transpose0_32x16, g_mipflag1_mipmodeidx13_transpose0_32x16,
          g_mipflag1_mipmodeidx14_transpose0_32x16, g_mipflag1_mipmodeidx15_transpose0_32x16);
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose1_32x16, g_mipflag1_mipmodeidx1_transpose1_32x16,
          g_mipflag1_mipmodeidx2_transpose1_32x16, g_mipflag1_mipmodeidx3_transpose1_32x16,
          g_mipflag1_mipmodeidx4_transpose1_32x16, g_mipflag1_mipmodeidx5_transpose1_32x16,
          g_mipflag1_mipmodeidx6_transpose1_32x16, g_mipflag1_mipmodeidx7_transpose1_32x16,
          g_mipflag1_mipmodeidx8_transpose1_32x16, g_mipflag1_mipmodeidx9_transpose1_32x16,
          g_mipflag1_mipmodeidx10_transpose1_32x16, g_mipflag1_mipmodeidx11_transpose1_32x16,
          g_mipflag1_mipmodeidx12_transpose1_32x16, g_mipflag1_mipmodeidx13_transpose1_32x16,
          g_mipflag1_mipmodeidx14_transpose1_32x16, g_mipflag1_mipmodeidx15_transpose1_32x16);
  fprintf(OutFile, "%d\n", g_Intra_32x16);

  fprintf(OutFile, "16x32:\t");
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose0_16x32, g_mipflag1_mipmodeidx1_transpose0_16x32,
          g_mipflag1_mipmodeidx2_transpose0_16x32, g_mipflag1_mipmodeidx3_transpose0_16x32,
          g_mipflag1_mipmodeidx4_transpose0_16x32, g_mipflag1_mipmodeidx5_transpose0_16x32,
          g_mipflag1_mipmodeidx6_transpose0_16x32, g_mipflag1_mipmodeidx7_transpose0_16x32,
          g_mipflag1_mipmodeidx8_transpose0_16x32, g_mipflag1_mipmodeidx9_transpose0_16x32,
          g_mipflag1_mipmodeidx10_transpose0_16x32, g_mipflag1_mipmodeidx11_transpose0_16x32,
          g_mipflag1_mipmodeidx12_transpose0_16x32, g_mipflag1_mipmodeidx13_transpose0_16x32,
          g_mipflag1_mipmodeidx14_transpose0_16x32, g_mipflag1_mipmodeidx15_transpose0_16x32);
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose1_16x32, g_mipflag1_mipmodeidx1_transpose1_16x32,
          g_mipflag1_mipmodeidx2_transpose1_16x32, g_mipflag1_mipmodeidx3_transpose1_16x32,
          g_mipflag1_mipmodeidx4_transpose1_16x32, g_mipflag1_mipmodeidx5_transpose1_16x32,
          g_mipflag1_mipmodeidx6_transpose1_16x32, g_mipflag1_mipmodeidx7_transpose1_16x32,
          g_mipflag1_mipmodeidx8_transpose1_16x32, g_mipflag1_mipmodeidx9_transpose1_16x32,
          g_mipflag1_mipmodeidx10_transpose1_16x32, g_mipflag1_mipmodeidx11_transpose1_16x32,
          g_mipflag1_mipmodeidx12_transpose1_16x32, g_mipflag1_mipmodeidx13_transpose1_16x32,
          g_mipflag1_mipmodeidx14_transpose1_16x32, g_mipflag1_mipmodeidx15_transpose1_16x32);
  fprintf(OutFile, "%d\n", g_Intra_16x32);

    fprintf(OutFile, "16x16:\t");
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose0_16x16, g_mipflag1_mipmodeidx1_transpose0_16x16,
          g_mipflag1_mipmodeidx2_transpose0_16x16, g_mipflag1_mipmodeidx3_transpose0_16x16,
          g_mipflag1_mipmodeidx4_transpose0_16x16, g_mipflag1_mipmodeidx5_transpose0_16x16,
          g_mipflag1_mipmodeidx6_transpose0_16x16, g_mipflag1_mipmodeidx7_transpose0_16x16,
          g_mipflag1_mipmodeidx8_transpose0_16x16, g_mipflag1_mipmodeidx9_transpose0_16x16,
          g_mipflag1_mipmodeidx10_transpose0_16x16, g_mipflag1_mipmodeidx11_transpose0_16x16,
          g_mipflag1_mipmodeidx12_transpose0_16x16, g_mipflag1_mipmodeidx13_transpose0_16x16,
          g_mipflag1_mipmodeidx14_transpose0_16x16, g_mipflag1_mipmodeidx15_transpose0_16x16);
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose1_16x16, g_mipflag1_mipmodeidx1_transpose1_16x16,
          g_mipflag1_mipmodeidx2_transpose1_16x16, g_mipflag1_mipmodeidx3_transpose1_16x16,
          g_mipflag1_mipmodeidx4_transpose1_16x16, g_mipflag1_mipmodeidx5_transpose1_16x16,
          g_mipflag1_mipmodeidx6_transpose1_16x16, g_mipflag1_mipmodeidx7_transpose1_16x16,
          g_mipflag1_mipmodeidx8_transpose1_16x16, g_mipflag1_mipmodeidx9_transpose1_16x16,
          g_mipflag1_mipmodeidx10_transpose1_16x16, g_mipflag1_mipmodeidx11_transpose1_16x16,
          g_mipflag1_mipmodeidx12_transpose1_16x16, g_mipflag1_mipmodeidx13_transpose1_16x16,
          g_mipflag1_mipmodeidx14_transpose1_16x16, g_mipflag1_mipmodeidx15_transpose1_16x16);
  fprintf(OutFile, "%d\n", g_Intra_16x16);

  fprintf(OutFile, "32x8:\t");
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose0_32x8, g_mipflag1_mipmodeidx1_transpose0_32x8,
          g_mipflag1_mipmodeidx2_transpose0_32x8, g_mipflag1_mipmodeidx3_transpose0_32x8,
          g_mipflag1_mipmodeidx4_transpose0_32x8, g_mipflag1_mipmodeidx5_transpose0_32x8,
          g_mipflag1_mipmodeidx6_transpose0_32x8, g_mipflag1_mipmodeidx7_transpose0_32x8,
          g_mipflag1_mipmodeidx8_transpose0_32x8, g_mipflag1_mipmodeidx9_transpose0_32x8,
          g_mipflag1_mipmodeidx10_transpose0_32x8, g_mipflag1_mipmodeidx11_transpose0_32x8,
          g_mipflag1_mipmodeidx12_transpose0_32x8, g_mipflag1_mipmodeidx13_transpose0_32x8,
          g_mipflag1_mipmodeidx14_transpose0_32x8, g_mipflag1_mipmodeidx15_transpose0_32x8);
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose1_32x8, g_mipflag1_mipmodeidx1_transpose1_32x8,
          g_mipflag1_mipmodeidx2_transpose1_32x8, g_mipflag1_mipmodeidx3_transpose1_32x8,
          g_mipflag1_mipmodeidx4_transpose1_32x8, g_mipflag1_mipmodeidx5_transpose1_32x8,
          g_mipflag1_mipmodeidx6_transpose1_32x8, g_mipflag1_mipmodeidx7_transpose1_32x8,
          g_mipflag1_mipmodeidx8_transpose1_32x8, g_mipflag1_mipmodeidx9_transpose1_32x8,
          g_mipflag1_mipmodeidx10_transpose1_32x8, g_mipflag1_mipmodeidx11_transpose1_32x8,
          g_mipflag1_mipmodeidx12_transpose1_32x8, g_mipflag1_mipmodeidx13_transpose1_32x8,
          g_mipflag1_mipmodeidx14_transpose1_32x8, g_mipflag1_mipmodeidx15_transpose1_32x8);
  fprintf(OutFile, "%d\n", g_Intra_32x8);

  fprintf(OutFile, "8x32:\t");
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose0_8x32, g_mipflag1_mipmodeidx1_transpose0_8x32,
          g_mipflag1_mipmodeidx2_transpose0_8x32, g_mipflag1_mipmodeidx3_transpose0_8x32,
          g_mipflag1_mipmodeidx4_transpose0_8x32, g_mipflag1_mipmodeidx5_transpose0_8x32,
          g_mipflag1_mipmodeidx6_transpose0_8x32, g_mipflag1_mipmodeidx7_transpose0_8x32,
          g_mipflag1_mipmodeidx8_transpose0_8x32, g_mipflag1_mipmodeidx9_transpose0_8x32,
          g_mipflag1_mipmodeidx10_transpose0_8x32, g_mipflag1_mipmodeidx11_transpose0_8x32,
          g_mipflag1_mipmodeidx12_transpose0_8x32, g_mipflag1_mipmodeidx13_transpose0_8x32,
          g_mipflag1_mipmodeidx14_transpose0_8x32, g_mipflag1_mipmodeidx15_transpose0_8x32);
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose1_8x32, g_mipflag1_mipmodeidx1_transpose1_8x32,
          g_mipflag1_mipmodeidx2_transpose1_8x32, g_mipflag1_mipmodeidx3_transpose1_8x32,
          g_mipflag1_mipmodeidx4_transpose1_8x32, g_mipflag1_mipmodeidx5_transpose1_8x32,
          g_mipflag1_mipmodeidx6_transpose1_8x32, g_mipflag1_mipmodeidx7_transpose1_8x32,
          g_mipflag1_mipmodeidx8_transpose1_8x32, g_mipflag1_mipmodeidx9_transpose1_8x32,
          g_mipflag1_mipmodeidx10_transpose1_8x32, g_mipflag1_mipmodeidx11_transpose1_8x32,
          g_mipflag1_mipmodeidx12_transpose1_8x32, g_mipflag1_mipmodeidx13_transpose1_8x32,
          g_mipflag1_mipmodeidx14_transpose1_8x32, g_mipflag1_mipmodeidx15_transpose1_8x32);
  fprintf(OutFile, "%d\n", g_Intra_8x32);

  fprintf(OutFile, "8x8:\t");
  fprintf(
    OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", g_mipflag1_mipmodeidx0_transpose0_8x8,
    g_mipflag1_mipmodeidx1_transpose0_8x8, g_mipflag1_mipmodeidx2_transpose0_8x8, g_mipflag1_mipmodeidx3_transpose0_8x8,
    g_mipflag1_mipmodeidx4_transpose0_8x8, g_mipflag1_mipmodeidx5_transpose0_8x8, g_mipflag1_mipmodeidx6_transpose0_8x8,
    g_mipflag1_mipmodeidx7_transpose0_8x8, g_mipflag1_mipmodeidx8_transpose0_8x8, g_mipflag1_mipmodeidx9_transpose0_8x8,
    g_mipflag1_mipmodeidx10_transpose0_8x8, g_mipflag1_mipmodeidx11_transpose0_8x8,
    g_mipflag1_mipmodeidx12_transpose0_8x8, g_mipflag1_mipmodeidx13_transpose0_8x8,
    g_mipflag1_mipmodeidx14_transpose0_8x8, g_mipflag1_mipmodeidx15_transpose0_8x8);
  fprintf(
    OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", g_mipflag1_mipmodeidx0_transpose1_8x8,
    g_mipflag1_mipmodeidx1_transpose1_8x8, g_mipflag1_mipmodeidx2_transpose1_8x8, g_mipflag1_mipmodeidx3_transpose1_8x8,
    g_mipflag1_mipmodeidx4_transpose1_8x8, g_mipflag1_mipmodeidx5_transpose1_8x8, g_mipflag1_mipmodeidx6_transpose1_8x8,
    g_mipflag1_mipmodeidx7_transpose1_8x8, g_mipflag1_mipmodeidx8_transpose1_8x8, g_mipflag1_mipmodeidx9_transpose1_8x8,
    g_mipflag1_mipmodeidx10_transpose1_8x8, g_mipflag1_mipmodeidx11_transpose1_8x8,
    g_mipflag1_mipmodeidx12_transpose1_8x8, g_mipflag1_mipmodeidx13_transpose1_8x8,
    g_mipflag1_mipmodeidx14_transpose1_8x8, g_mipflag1_mipmodeidx15_transpose1_8x8);
  fprintf(OutFile, "%d\n", g_Intra_8x8);

  fprintf(OutFile, "8x4:\t");
  fprintf(
    OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", g_mipflag1_mipmodeidx0_transpose0_8x4,
    g_mipflag1_mipmodeidx1_transpose0_8x4, g_mipflag1_mipmodeidx2_transpose0_8x4, g_mipflag1_mipmodeidx3_transpose0_8x4,
    g_mipflag1_mipmodeidx4_transpose0_8x4, g_mipflag1_mipmodeidx5_transpose0_8x4, g_mipflag1_mipmodeidx6_transpose0_8x4,
    g_mipflag1_mipmodeidx7_transpose0_8x4, g_mipflag1_mipmodeidx8_transpose0_8x4, g_mipflag1_mipmodeidx9_transpose0_8x4,
    g_mipflag1_mipmodeidx10_transpose0_8x4, g_mipflag1_mipmodeidx11_transpose0_8x4,
    g_mipflag1_mipmodeidx12_transpose0_8x4, g_mipflag1_mipmodeidx13_transpose0_8x4,
    g_mipflag1_mipmodeidx14_transpose0_8x4, g_mipflag1_mipmodeidx15_transpose0_8x4);
  fprintf(
    OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", g_mipflag1_mipmodeidx0_transpose1_8x4,
    g_mipflag1_mipmodeidx1_transpose1_8x4, g_mipflag1_mipmodeidx2_transpose1_8x4, g_mipflag1_mipmodeidx3_transpose1_8x4,
    g_mipflag1_mipmodeidx4_transpose1_8x4, g_mipflag1_mipmodeidx5_transpose1_8x4, g_mipflag1_mipmodeidx6_transpose1_8x4,
    g_mipflag1_mipmodeidx7_transpose1_8x4, g_mipflag1_mipmodeidx8_transpose1_8x4, g_mipflag1_mipmodeidx9_transpose1_8x4,
    g_mipflag1_mipmodeidx10_transpose1_8x4, g_mipflag1_mipmodeidx11_transpose1_8x4,
    g_mipflag1_mipmodeidx12_transpose1_8x4, g_mipflag1_mipmodeidx13_transpose1_8x4,
    g_mipflag1_mipmodeidx14_transpose1_8x4, g_mipflag1_mipmodeidx15_transpose1_8x4);
  fprintf(OutFile, "%d\n", g_Intra_8x4);

  fprintf(OutFile, "4x8:\t");
  fprintf(
    OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", g_mipflag1_mipmodeidx0_transpose0_4x8,
    g_mipflag1_mipmodeidx1_transpose0_4x8, g_mipflag1_mipmodeidx2_transpose0_4x8, g_mipflag1_mipmodeidx3_transpose0_4x8,
    g_mipflag1_mipmodeidx4_transpose0_4x8, g_mipflag1_mipmodeidx5_transpose0_4x8, g_mipflag1_mipmodeidx6_transpose0_4x8,
    g_mipflag1_mipmodeidx7_transpose0_4x8, g_mipflag1_mipmodeidx8_transpose0_4x8, g_mipflag1_mipmodeidx9_transpose0_4x8,
    g_mipflag1_mipmodeidx10_transpose0_4x8, g_mipflag1_mipmodeidx11_transpose0_4x8,
    g_mipflag1_mipmodeidx12_transpose0_4x8, g_mipflag1_mipmodeidx13_transpose0_4x8,
    g_mipflag1_mipmodeidx14_transpose0_4x8, g_mipflag1_mipmodeidx15_transpose0_4x8);
  fprintf(
    OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", g_mipflag1_mipmodeidx0_transpose1_4x8,
    g_mipflag1_mipmodeidx1_transpose1_4x8, g_mipflag1_mipmodeidx2_transpose1_4x8, g_mipflag1_mipmodeidx3_transpose1_4x8,
    g_mipflag1_mipmodeidx4_transpose1_4x8, g_mipflag1_mipmodeidx5_transpose1_4x8, g_mipflag1_mipmodeidx6_transpose1_4x8,
    g_mipflag1_mipmodeidx7_transpose1_4x8, g_mipflag1_mipmodeidx8_transpose1_4x8, g_mipflag1_mipmodeidx9_transpose1_4x8,
    g_mipflag1_mipmodeidx10_transpose1_4x8, g_mipflag1_mipmodeidx11_transpose1_4x8,
    g_mipflag1_mipmodeidx12_transpose1_4x8, g_mipflag1_mipmodeidx13_transpose1_4x8,
    g_mipflag1_mipmodeidx14_transpose1_4x8, g_mipflag1_mipmodeidx15_transpose1_4x8);
  fprintf(OutFile, "%d\n", g_Intra_4x8);

  fprintf(OutFile, "32x4:\t");
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose0_32x4, g_mipflag1_mipmodeidx1_transpose0_32x4,
          g_mipflag1_mipmodeidx2_transpose0_32x4, g_mipflag1_mipmodeidx3_transpose0_32x4,
          g_mipflag1_mipmodeidx4_transpose0_32x4, g_mipflag1_mipmodeidx5_transpose0_32x4,
          g_mipflag1_mipmodeidx6_transpose0_32x4, g_mipflag1_mipmodeidx7_transpose0_32x4,
          g_mipflag1_mipmodeidx8_transpose0_32x4, g_mipflag1_mipmodeidx9_transpose0_32x4,
          g_mipflag1_mipmodeidx10_transpose0_32x4, g_mipflag1_mipmodeidx11_transpose0_32x4,
          g_mipflag1_mipmodeidx12_transpose0_32x4, g_mipflag1_mipmodeidx13_transpose0_32x4,
          g_mipflag1_mipmodeidx14_transpose0_32x4, g_mipflag1_mipmodeidx15_transpose0_32x4);
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose1_32x4, g_mipflag1_mipmodeidx1_transpose1_32x4,
          g_mipflag1_mipmodeidx2_transpose1_32x4, g_mipflag1_mipmodeidx3_transpose1_32x4,
          g_mipflag1_mipmodeidx4_transpose1_32x4, g_mipflag1_mipmodeidx5_transpose1_32x4,
          g_mipflag1_mipmodeidx6_transpose1_32x4, g_mipflag1_mipmodeidx7_transpose1_32x4,
          g_mipflag1_mipmodeidx8_transpose1_32x4, g_mipflag1_mipmodeidx9_transpose1_32x4,
          g_mipflag1_mipmodeidx10_transpose1_32x4, g_mipflag1_mipmodeidx11_transpose1_32x4,
          g_mipflag1_mipmodeidx12_transpose1_32x4, g_mipflag1_mipmodeidx13_transpose1_32x4,
          g_mipflag1_mipmodeidx14_transpose1_32x4, g_mipflag1_mipmodeidx15_transpose1_32x4);
  fprintf(OutFile, "%d\n", g_Intra_32x4);

  fprintf(OutFile, "4x32:\t");
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose0_4x32, g_mipflag1_mipmodeidx1_transpose0_4x32,
          g_mipflag1_mipmodeidx2_transpose0_4x32, g_mipflag1_mipmodeidx3_transpose0_4x32,
          g_mipflag1_mipmodeidx4_transpose0_4x32, g_mipflag1_mipmodeidx5_transpose0_4x32,
          g_mipflag1_mipmodeidx6_transpose0_4x32, g_mipflag1_mipmodeidx7_transpose0_4x32,
          g_mipflag1_mipmodeidx8_transpose0_4x32, g_mipflag1_mipmodeidx9_transpose0_4x32,
          g_mipflag1_mipmodeidx10_transpose0_4x32, g_mipflag1_mipmodeidx11_transpose0_4x32,
          g_mipflag1_mipmodeidx12_transpose0_4x32, g_mipflag1_mipmodeidx13_transpose0_4x32,
          g_mipflag1_mipmodeidx14_transpose0_4x32, g_mipflag1_mipmodeidx15_transpose0_4x32);
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose1_4x32, g_mipflag1_mipmodeidx1_transpose1_4x32,
          g_mipflag1_mipmodeidx2_transpose1_4x32, g_mipflag1_mipmodeidx3_transpose1_4x32,
          g_mipflag1_mipmodeidx4_transpose1_4x32, g_mipflag1_mipmodeidx5_transpose1_4x32,
          g_mipflag1_mipmodeidx6_transpose1_4x32, g_mipflag1_mipmodeidx7_transpose1_4x32,
          g_mipflag1_mipmodeidx8_transpose1_4x32, g_mipflag1_mipmodeidx9_transpose1_4x32,
          g_mipflag1_mipmodeidx10_transpose1_4x32, g_mipflag1_mipmodeidx11_transpose1_4x32,
          g_mipflag1_mipmodeidx12_transpose1_4x32, g_mipflag1_mipmodeidx13_transpose1_4x32,
          g_mipflag1_mipmodeidx14_transpose1_4x32, g_mipflag1_mipmodeidx15_transpose1_4x32);
  fprintf(OutFile, "%d\n", g_Intra_4x32);

  fprintf(OutFile, "16x4:\t");
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose0_16x4, g_mipflag1_mipmodeidx1_transpose0_16x4,
          g_mipflag1_mipmodeidx2_transpose0_16x4, g_mipflag1_mipmodeidx3_transpose0_16x4,
          g_mipflag1_mipmodeidx4_transpose0_16x4, g_mipflag1_mipmodeidx5_transpose0_16x4,
          g_mipflag1_mipmodeidx6_transpose0_16x4, g_mipflag1_mipmodeidx7_transpose0_16x4,
          g_mipflag1_mipmodeidx8_transpose0_16x4, g_mipflag1_mipmodeidx9_transpose0_16x4,
          g_mipflag1_mipmodeidx10_transpose0_16x4, g_mipflag1_mipmodeidx11_transpose0_16x4,
          g_mipflag1_mipmodeidx12_transpose0_16x4, g_mipflag1_mipmodeidx13_transpose0_16x4,
          g_mipflag1_mipmodeidx14_transpose0_16x4, g_mipflag1_mipmodeidx15_transpose0_16x4);
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose1_16x4, g_mipflag1_mipmodeidx1_transpose1_16x4,
          g_mipflag1_mipmodeidx2_transpose1_16x4, g_mipflag1_mipmodeidx3_transpose1_16x4,
          g_mipflag1_mipmodeidx4_transpose1_16x4, g_mipflag1_mipmodeidx5_transpose1_16x4,
          g_mipflag1_mipmodeidx6_transpose1_16x4, g_mipflag1_mipmodeidx7_transpose1_16x4,
          g_mipflag1_mipmodeidx8_transpose1_16x4, g_mipflag1_mipmodeidx9_transpose1_16x4,
          g_mipflag1_mipmodeidx10_transpose1_16x4, g_mipflag1_mipmodeidx11_transpose1_16x4,
          g_mipflag1_mipmodeidx12_transpose1_16x4, g_mipflag1_mipmodeidx13_transpose1_16x4,
          g_mipflag1_mipmodeidx14_transpose1_16x4, g_mipflag1_mipmodeidx15_transpose1_16x4);
  fprintf(OutFile, "%d\n", g_Intra_16x4);

  fprintf(OutFile, "4x16:\t");
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose0_4x16, g_mipflag1_mipmodeidx1_transpose0_4x16,
          g_mipflag1_mipmodeidx2_transpose0_4x16, g_mipflag1_mipmodeidx3_transpose0_4x16,
          g_mipflag1_mipmodeidx4_transpose0_4x16, g_mipflag1_mipmodeidx5_transpose0_4x16,
          g_mipflag1_mipmodeidx6_transpose0_4x16, g_mipflag1_mipmodeidx7_transpose0_4x16,
          g_mipflag1_mipmodeidx8_transpose0_4x16, g_mipflag1_mipmodeidx9_transpose0_4x16,
          g_mipflag1_mipmodeidx10_transpose0_4x16, g_mipflag1_mipmodeidx11_transpose0_4x16,
          g_mipflag1_mipmodeidx12_transpose0_4x16, g_mipflag1_mipmodeidx13_transpose0_4x16,
          g_mipflag1_mipmodeidx14_transpose0_4x16, g_mipflag1_mipmodeidx15_transpose0_4x16);
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t",
          g_mipflag1_mipmodeidx0_transpose1_4x16, g_mipflag1_mipmodeidx1_transpose1_4x16,
          g_mipflag1_mipmodeidx2_transpose1_4x16, g_mipflag1_mipmodeidx3_transpose1_4x16,
          g_mipflag1_mipmodeidx4_transpose1_4x16, g_mipflag1_mipmodeidx5_transpose1_4x16,
          g_mipflag1_mipmodeidx6_transpose1_4x16, g_mipflag1_mipmodeidx7_transpose1_4x16,
          g_mipflag1_mipmodeidx8_transpose1_4x16, g_mipflag1_mipmodeidx9_transpose1_4x16,
          g_mipflag1_mipmodeidx10_transpose1_4x16, g_mipflag1_mipmodeidx11_transpose1_4x16,
          g_mipflag1_mipmodeidx12_transpose1_4x16, g_mipflag1_mipmodeidx13_transpose1_4x16,
          g_mipflag1_mipmodeidx14_transpose1_4x16, g_mipflag1_mipmodeidx15_transpose1_4x16);
  fprintf(OutFile, "%d\n", g_Intra_4x16);

  fprintf(OutFile, "4x4:\t");
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", g_mipflag1_mipmodeidx0_transpose0_4x4,
    g_mipflag1_mipmodeidx1_transpose0_4x4, g_mipflag1_mipmodeidx2_transpose0_4x4, g_mipflag1_mipmodeidx3_transpose0_4x4,
    g_mipflag1_mipmodeidx4_transpose0_4x4, g_mipflag1_mipmodeidx5_transpose0_4x4, g_mipflag1_mipmodeidx6_transpose0_4x4,
    g_mipflag1_mipmodeidx7_transpose0_4x4, g_mipflag1_mipmodeidx8_transpose0_4x4, g_mipflag1_mipmodeidx9_transpose0_4x4,
    g_mipflag1_mipmodeidx10_transpose0_4x4, g_mipflag1_mipmodeidx11_transpose0_4x4,
    g_mipflag1_mipmodeidx12_transpose0_4x4, g_mipflag1_mipmodeidx13_transpose0_4x4,
    g_mipflag1_mipmodeidx14_transpose0_4x4, g_mipflag1_mipmodeidx15_transpose0_4x4);
  fprintf(OutFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", g_mipflag1_mipmodeidx0_transpose1_4x4,
    g_mipflag1_mipmodeidx1_transpose1_4x4, g_mipflag1_mipmodeidx2_transpose1_4x4, g_mipflag1_mipmodeidx3_transpose1_4x4,
    g_mipflag1_mipmodeidx4_transpose1_4x4, g_mipflag1_mipmodeidx5_transpose1_4x4, g_mipflag1_mipmodeidx6_transpose1_4x4,
    g_mipflag1_mipmodeidx7_transpose1_4x4, g_mipflag1_mipmodeidx8_transpose1_4x4, g_mipflag1_mipmodeidx9_transpose1_4x4,
    g_mipflag1_mipmodeidx10_transpose1_4x4, g_mipflag1_mipmodeidx11_transpose1_4x4,
    g_mipflag1_mipmodeidx12_transpose1_4x4, g_mipflag1_mipmodeidx13_transpose1_4x4,
    g_mipflag1_mipmodeidx14_transpose1_4x4, g_mipflag1_mipmodeidx15_transpose1_4x4);
  fprintf(OutFile, "%d\n", g_Intra_4x4);

  fclose(OutFile);
#endif

  // ending time
  dResult = (double)(clock()-lBefore) / CLOCKS_PER_SEC;
  printf("\n Total Time: %12.3f sec.\n", dResult);



  delete pcDecApp;

  return returnCode;
}

//! \}
