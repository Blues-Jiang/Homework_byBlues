import pygame
import random
import copy

class snake:
    def __init__(self):
        """
        init the snake
        """
        self.poslist = [[10,10]]
    def position(self):
        """
        return the all of the snake's point
        """
        return self.poslist
    def gowhere(self,where):
        """
        change the snake's point to control the snake's moving direction
        """
        count = len(self.poslist)
        pos = count-1
        while pos > 0:
            self.poslist[pos] = copy.deepcopy(self.poslist[pos-1])
            pos -= 1
        if where is 'U':
            self.poslist[pos][1] -= 10
            if self.poslist[pos][1] < 0:
                self.poslist[pos][1] = 500
        if where is 'D':
            self.poslist[pos][1] += 10
            if self.poslist[pos][1] > 500:
                self.poslist[pos][1] = 0
        if where is 'L':
            self.poslist[pos][0] -= 10
            if self.poslist[pos][0] < 0:
                self.poslist[pos][0] = 500
        if where is 'R':
            self.poslist[pos][0] += 10
            if self.poslist[pos][0] > 500:
                self.poslist[pos][0] = 0
    def eatfood(self,foodpoint):
        """
        eat the food and add point to snake
        """
        self.poslist.append(foodpoint)

class food:
    def __init__(self):
        """
        init the food's point
        """
        self.x = random.randint(10,490)
        self.y = random.randint(10,490)
    def display(self):
        """
        init the food's point and return the point
        """
        self.x = random.randint(10,490)
        self.y = random.randint(10,490)
        return self.position()
    def position(self):
        """
        return the food's point
        """
        return [self.x,self.y]

def main():
    moveup = False
    movedown = False
    moveleft = False
    moveright = True
    pygame.init()
    clock = pygame.time.Clock()
    width = 500
    height = 500
    screen = pygame.display.set_mode([width,height])
    restart = True
    while restart:
        sk = snake()
        fd = food()
        screentitle = pygame.display.set_caption("eat snake")
        sk.gowhere('R')
        running = True
        while running:
            # fill the background is white
            screen.fill([255,255,255])
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    exit(0)
                # judge the down key
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_UP:
                        moveup = True
                        movedown = False
                        moveleft = False
                        moveright = False
                    if event.key == pygame.K_DOWN:
                        moveup = False
                        movedown = True
                        moveleft = False
                        moveright = False
                    if event.key == pygame.K_LEFT:
                        moveup = False
                        movedown = False
                        moveleft = True
                        moveright = False
                    if event.key == pygame.K_RIGHT:
                        moveup = False
                        movedown = False
                        moveleft = False
                        moveright = True
            # where the snake goes
            time_pass = clock.tick(40)
            if moveup:
                sk.gowhere('U')
            if movedown:
                sk.gowhere('D')
            if moveleft:
                sk.gowhere('L')
            if moveright:
                sk.gowhere('R')
            # draw the food
            poslist = sk.position()
            foodpoint = fd.position()
            fdrect = pygame.draw.circle(screen,[255,0,0],foodpoint,15,0)
            # draw the snafe
            snaferect = []
            for pos in poslist:
                snaferect.append(pygame.draw.circle(screen,[255,0,0],pos,5,0))
                # crash test if the snake eat food
                if fdrect.collidepoint(pos):
                    foodpoint = fd.display()
                    sk.eatfood(foodpoint)
                    fdrect = pygame.draw.circle(screen,[255,0,0],foodpoint,15,0)
                    break
            # crash test if the snake crash itsself
            headrect = snaferect[0]
            count = len(snaferect)
            while count > 1:
                if headrect.colliderect(snaferect[count-1]):
                    running = False
                count -= 1
            pygame.display.update()
        # game over background
        pygame.font.init()
        screen.fill([100,0,0])
        font = pygame.font.Font(None,48)
        text = font.render("Game Over !!!",True,(255,0,0))
        textRect = text.get_rect()
        textRect.centerx = screen.get_rect().centerx
        textRect.centery = screen.get_rect().centery + 24
        screen.blit(text,textRect)
        # keydown r restart,keydown n exit
        while 1:
            event = pygame.event.poll()
            if event.type == pygame.QUIT:
                pygame.quit()
                exit(0)
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_r:
                    restart = True
                    del sk
                    del fd
                    break
                if event.key == pygame.K_n:
                    restart = False
                    break
            pygame.display.update()


if __name__=='__main__':
    main()
