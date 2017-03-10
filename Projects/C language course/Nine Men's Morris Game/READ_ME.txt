This is my first year project, for C language.
To run game:
1. Open MlynekGra.cbp in CodeBlocks
2. Select the 'Compiler Settings' Tab, then 'Other Options' tab.
3. Add `pkg-config gtk+-3.0 --cflags`, click ok.
4. Click 'Linker Settings' Tab
5. Under "Other Linker Options" add (or modify) `pkg-config gtk+-3.0 --libs` click ok.
6. Build and run project.
7. Enjoy. :)
