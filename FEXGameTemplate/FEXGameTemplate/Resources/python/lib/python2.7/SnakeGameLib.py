import FEX
import sys
import json
import string

controller_1 = None
hero = None
game = None
mapw = 10
maph = 10


def make_shared_ptr( p ):
    p.__disown__()
    ret = FEX.make_gameobj_ptr(p)
    return ret

def grid_to_gl(point):
    return FEX.CCPoint(point.x*5+100,point.y*5+100)

class Dot(FEX.SpriteBase):
    def __init__(self,point):
        print "new snake spawned"
        FEX.SpriteBase.__init__( self, grid_to_gl(point) ,FEX.map_string_string({ "sprite_desc" : "dot"}) )
        self.light()
    def light(self):
        for i in self.get_components():
            i.play_anim("light")
            print "component : ",i

class GameSnake(FEX.GameBase):

    def __init__(self):
        self.dots=[]
        FEX.GameBase.__init__(self)
        FEX.set_game( self )
        self.should_end = False
        for i in range(mapw):
            for j in range(maph):
                self.dots.append(self.create_dot(i,j,0))
    
    
    def create_dot(self,x,y,color):
        snake = make_shared_ptr(Dot(FEX.CCPoint(x,y)))
        print FEX.get_game()
        FEX.get_game().add_game_object(snake,"root")
        return snake
    
    def refresh_map(self,map_data):
        pass
        
    
    def update(self, *args):
        FEX.GameBase.update(self, *args)
        refresh_map(None)



def run_game():
    print sys.path
    global game
    global controller_1
    global hero
    game = GameSnake()
    game.__disown__()



