/*
 * vicefilepanel.h - handle VICE open and save panels
 *
 * Written by
 *  Christian Vogelgsang <chris@vogelgsang.org>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#import <Cocoa/Cocoa.h>

@interface VICEFilePanel : NSObject <NSOpenSavePanelDelegate>
{
    NSDictionary *extensionMap;

    // Image Contents in OpenFile
    NSArray                    *imageContentsEmpty;
    IBOutlet NSTextField       *imageContentsHeader;
    IBOutlet NSTextField       *imageContentsFooter;
    IBOutlet NSView            *imageContentsView;
    IBOutlet NSArrayController *imageContentsController;
    IBOutlet NSButton          *autostartButton;
    
    BOOL selectedAutostart;
    int  selectedProgNum;
}

- (NSString *)pickOpenFileWithPreviewAndType:(NSString *)type allowRun:(BOOL)allowRun;
@property (readonly) int selectedProgNum;
@property (readonly) BOOL selectedAutostart;

- (NSString *)pickOpenFileWithType:(NSString *)type;
- (NSString *)pickSaveFileWithType:(NSString *)type;

- (NSString *)pickOpenFileWithTitle:(NSString *)title types:(NSArray<NSString*> *)types;
- (NSString *)pickSaveFileWithTitle:(NSString *)title types:(NSArray<NSString*> *)types;
- (NSString *)pickDirectoryWithTitle:(NSString *)title;

- (NSArray *)pickAttachFileWithTitle:(NSString *)title andTypeDictionary:(NSDictionary *)types defaultType:(NSString *)defaultType;

@end
