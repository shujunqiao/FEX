//
//  DataSources.h
//  Editor
//
//  Created by Fancyzero on 13-8-4.
//
//

#import <Foundation/Foundation.h>

@interface SpriteClassDataSource : NSObject<NSComboBoxCellDataSource>
{
@public
	NSMutableArray*	sprite_classes;
}

-(void) collect_classes;

@end
@interface SpriteDescDataSource : NSObject<NSComboBoxCellDataSource>
{
}
@end


@interface SpriteSpawnParamsDataSource : NSObject<NSTableViewDataSource>

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView;
- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;
- (void)tableView:(NSTableView *)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row;
@end;

@interface MyTableViewDelegate : NSObject<NSTableViewDelegate>
- (NSCell *)tableView:(NSTableView *)tableView dataCellForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row ;
@end;