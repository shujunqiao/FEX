//
//  DataSources.m
//  Editor
//
//  Created by Fancyzero on 13-8-4.
//
//

#import "DataSources.h"
#import "FE.h"
#import "GameSADEditorLevel.h"
#import "ResourceManager.h"
#import "AppController.h"

@implementation SpriteClassDataSource
-(id) init
{
	self = [super init];
	sprite_classes = [NSMutableArray array];
    [sprite_classes retain];
	return self;
}

- (NSInteger)numberOfItemsInComboBoxCell:(NSComboBoxCell *)comboBoxCell
{
	if ( sprite_classes != nil )
		return [sprite_classes count];
	else
		return 0;
}

- (id)comboBoxCell:(NSComboBoxCell *)aComboBoxCell objectValueForItemAtIndex:(NSInteger)index
{
	if ( sprite_classes == nil )
		return NULL;
	
	if (index > [sprite_classes count] || index < 0  )
		return nil;
	return [sprite_classes objectAtIndex:index ];
	
}

-(void) collect_classes
{
    [sprite_classes removeAllObjects];
    auto classes = FESimple::GameObjFactory::get_all_classes();
    for ( auto i : classes )
    {
        [sprite_classes addObject: [NSString stringWithUTF8String: i->name.c_str()]];
    }
}

@end

LevelTrigger& current_trigger()
{
    return get_editor_level()->get_current_trigger();
}

@implementation SpriteDescDataSource

- (NSInteger)numberOfItemsInComboBoxCell:(NSComboBoxCell *)comboBoxCell
{
    return FESimple::ResourceManager::instance()->sprite_descs.size();
}


- (id)comboBoxCell:(NSComboBoxCell *)aComboBoxCell objectValueForItemAtIndex:(NSInteger)index
{
    auto i = FESimple::ResourceManager::instance()->sprite_descs.begin();
    while( index-- > 0)
        i++;
    std::string name = i->first;
    return [NSString stringWithUTF8String:name.c_str()];
}

@end

@implementation SpriteSpawnParamsDataSource

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView
{
    if ( get_editor_level() )
    {
        return current_trigger().params.size();
    }
	return 0;
}



- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
	
    if ( get_editor_level() )
    {
        auto it = current_trigger().params.begin();
        
        for ( int i = 0; it != current_trigger().params.end(); ++it, i++ )
        {
            if ( i == row )
            {
                if ( [tableColumn.identifier isEqualToString: @"col_key"])
                    return [NSString stringWithUTF8String: it->first.c_str()];
                
                if ( [tableColumn.identifier isEqualToString: @"col_value"])
                    return [NSString stringWithUTF8String: it->second.c_str()];
                
                return nil;
            }
        }
    }
    
	return NULL;
}

- (void)tableView:(NSTableView *)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    auto& params = current_trigger().params;
    
    NSLog(@"%@",object);
    if ( get_editor_level() == nullptr )
        return;
    if ( [tableColumn.identifier isEqualToString: @"col_value"])
    {
        auto it = params.begin();
        std::advance( it , row );
        it->second = [object UTF8String];
    }
    if ( [tableColumn.identifier isEqualToString: @"col_key"])
    {
        auto it = params.begin();
        std::advance( it , row );
        auto value = it->second;
        params.erase(it);
        params[[object UTF8String] ] = value;
    }
    [tableView reloadData];
}

@end

@implementation MyTableViewDelegate

-(IBAction)seltest:(id)sender
{
    NSLog(@"test called");
}

- (NSCell *)tableView:(NSTableView *)tableView dataCellForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    if ( [tableColumn.identifier isEqualToString: @"col_value"])
    {
        auto it = current_trigger().params.begin();
        std::advance( it , row );
        
        if ( it->first == "class")
        {
            NSComboBoxCell* cb = [[[NSComboBoxCell alloc] init] autorelease];
            AppController* apc = [NSApplication sharedApplication].delegate;
            [cb setUsesDataSource: YES];
            [cb setDataSource: apc.sprite_class_datasource];
            [cb setEditable: YES];
            [cb setCompletes: YES];
            return cb;
        }
        if ( it->first == "sprite_desc" )
        {
            NSComboBoxCell* cb = [[[NSComboBoxCell alloc] init] autorelease];
            AppController* apc = [NSApplication sharedApplication].delegate;
            [cb setUsesDataSource: YES];
            [cb setDataSource: apc.sprite_desc_data_source];
            [cb setEditable: YES];
            [cb setCompletes: YES];
            return cb;
        }
        
    }
    return [tableColumn dataCell];
}


@end