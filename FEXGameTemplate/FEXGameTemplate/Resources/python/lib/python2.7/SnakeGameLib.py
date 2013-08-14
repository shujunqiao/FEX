import FEX
import sys
controller_1 = None
hero = None
game = None

def make_shared_ptr( p ):
    p.__disown__()
    ret = FEX.make_gameobj_ptr(p)
    return ret

def grid_to_gl(x,y):
    return x*32,y*32

class Snake(FEX.SpriteBase):
    body=[]
    heading = 0 #0,1,2,3 up down left right
    def __init__(self,point):
        print "new snake spawned"
        self.body.append({0,0})
        print self.body[0]
        print point.x
        print point.y
        FEX.SpriteBase.__init__( self, point ,FEX.map_string_string({ "sprite_desc" : "coin"}) )
        self.update_body_component()
    
    def update_body_component(self):
        pass



class GameSnake(FEX.GameBase):

    def __init__(self):
        print grid_to_gl(300,300)
        FEX.GameBase.__init__(self)
        FEX.set_game( self )
        self.should_end = False
        self.create_snake(300,300,10)
    
    def create_snake(self,x,y,color):
        snake = make_shared_ptr(Snake(FEX.CCPoint(x,y)))
        print FEX.get_game()
        FEX.get_game().add_game_object(snake,"root")
    
    def update(self, *args):
        FEX.GameBase.update(self, *args)




def run_game():
    print sys.path
    global game
    global controller_1
    global hero
    game = GameSnake()
    game.__disown__()



