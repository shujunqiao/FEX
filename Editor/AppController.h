/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#pragma once

#import "cocos2d.h"
#import "EAGLView.h"
#import "DataSources.h"
@interface AppController : NSObject <NSApplicationDelegate>
{
    NSWindow *window;
    EAGLView *glView;
    SpriteClassDataSource *sprite_class_datasource;
    SpriteSpawnParamsDataSource *sprite_spawnparams_datasource;
    SpriteDescDataSource *sprite_desc_data_source;
    MyTableViewDelegate *table_view_delegate;
    NSTableView *table_view_spawn_params;
    NSPanel *property_window;
}

@property (assign) IBOutlet NSPanel *property_window;

@property (assign) IBOutlet SpriteClassDataSource *sprite_class_datasource;
@property (nonatomic, assign) IBOutlet NSWindow* window;
@property (nonatomic, assign) IBOutlet EAGLView* glView;

@property (assign) IBOutlet SpriteSpawnParamsDataSource *sprite_spawnparams_datasource;
@property (assign) IBOutlet SpriteDescDataSource *sprite_desc_data_source;
@property (assign) IBOutlet MyTableViewDelegate *table_view_delegate;
@property (assign) IBOutlet NSTableView *table_view_spawn_params;

-(IBAction) classChanged:(NSComboBox*)sender;
-(IBAction) switchEditMode:(NSSegmentedControl*)sender;
-(IBAction) openDocument:(id)sender;
-(IBAction) toggleFullScreen:(id)sender;
-(IBAction) exitFullScreen:(id)sender;
- (IBAction)addProperty:(id)sender;
- (IBAction)removeProperty:(id)sender;

@end
