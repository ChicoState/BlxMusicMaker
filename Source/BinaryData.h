/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   NoiseH_png;
    const int            NoiseH_pngSize = 1914;

    extern const char*   NoiseNP_png;
    const int            NoiseNP_pngSize = 1915;

    extern const char*   NoiseP_png;
    const int            NoiseP_pngSize = 1900;

    extern const char*   Pulse25H_png;
    const int            Pulse25H_pngSize = 508;

    extern const char*   Pulse25NP_png;
    const int            Pulse25NP_pngSize = 500;

    extern const char*   Pulse25P_png;
    const int            Pulse25P_pngSize = 508;

    extern const char*   Pulse50H_png;
    const int            Pulse50H_pngSize = 509;

    extern const char*   Pulse50NP_png;
    const int            Pulse50NP_pngSize = 499;

    extern const char*   Pulse50P_png;
    const int            Pulse50P_pngSize = 508;

    extern const char*   Pulse75H_png;
    const int            Pulse75H_pngSize = 507;

    extern const char*   Pulse75NP_png;
    const int            Pulse75NP_pngSize = 497;

    extern const char*   Pulse75P_png;
    const int            Pulse75P_pngSize = 503;

    extern const char*   SawH_png;
    const int            SawH_pngSize = 1530;

    extern const char*   SawNP_png;
    const int            SawNP_pngSize = 1505;

    extern const char*   SawP_png;
    const int            SawP_pngSize = 1465;

    extern const char*   SineH_png;
    const int            SineH_pngSize = 1781;

    extern const char*   SineNP_png;
    const int            SineNP_pngSize = 1873;

    extern const char*   SineP_png;
    const int            SineP_pngSize = 1856;

    extern const char*   TriangleH_png;
    const int            TriangleH_pngSize = 1789;

    extern const char*   TriangleNP_png;
    const int            TriangleNP_pngSize = 1757;

    extern const char*   TriangleP_png;
    const int            TriangleP_pngSize = 1769;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 21;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
