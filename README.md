# H5_bitmap_exporter
basic tool to convert halo 5's bitmap tag files to usable png/jpeg files, thanks to Plastered Crab's work on the texture unswizzling

only 2d textures should work, there is currently no support for: texture arrays, cubemaps, 1d textures & 3d textures

to get the standalone bitmap files, you'll need to unpack the game's module files (im not familiar with the tool to do that)

to convert bitmaps from the xbox version (detile/unswizzle), you will require the xg.dll & kernelx.dll (put them into the same folder as the exe is built to)


also, im not the best at C++, so you can expect a tiny memory leak (which just means if you're dumping the entire game's bitmaps, the process might end up stacking up an extra 100mb of ram or something like that, which is then freed when the process closes)
