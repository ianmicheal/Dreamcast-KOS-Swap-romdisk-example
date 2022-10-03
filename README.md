# Dreamcast-KOS-Swap-romdisk-example
Example based on the code posted  by black aura on  Fri Jul 08, 2005 11:29 am And example by tonma  Mon Apr 25, 2016 5:28 am fixed and update for kos2.0 by Ian micheal Sun Oct 2022 11:09pm Added drawing image from png example kos Fixed missing "/' and fs_chdir("/romdisk3/");


One Example use
It's an easy way to avoid gdrom blocking and playing music while loading files from the cdr.. can have a loading screen play the music and still load all your data files at the same time then unmount the romdisk etc no skipping 


By loading a romdisk from cd and not baked in you can manage memory and after  it's loaded each level umount it..

Faster file loading once loaded not using the slow mil cd read speed and also being able to read from it and the cd at the same time
Not causing gdrom blocking..

Included example shows loading a romdisk from /cd/ mounting it changing to dir and loading a png to texture to the pvr.. and also unmounting it
Ready for the next level.. 

In the make file it's easy to make your new romdisk place the files in romdisk folder change the src to point to them..
word of warning to change your dir when you read files from the other mount points this seems to missing in most of the guides

example fs_chdir("/cd/"); to read back off the cd

Futher info is here https://dcemulation.org/index.php?title=Romdisk_Swapping
and here https://dcemulation.org/phpBB/viewtopic.php?f=29&t=68795&hilit=romdisk+feet+of+fury

