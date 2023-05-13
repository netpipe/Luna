from random import random,randint,choice
import time
import copy
from trig import *
import json
from multiprocessing.pool import ThreadPool
import pygame as pg
import os

train=True
id=100
def newId():
    global id
    id+=1
    return id

def gaussianRandom(max,sample,offset):
    return sum([random()*max for _ in range(sample)])/sample + offset

def radians(degrees):
    return degrees*3.1415/180
def distance(x,y):
    if isinstance(x,float) or isinstance(x,int):
        return pow(pow(x,2)+pow(y,2),0.5)
    else:
        return x[0]-y[0],x[1]-y[1],pow(pow(x[0]-y[0],2)+pow(x[1]-y[1],2),0.5)
    
def matrix_multiply(A, B):
    if len(A[0]) != len(B):
        raise ValueError("Incompatible matrix dimensions for multiplication")

    result = [[0 for _ in range(len(B[0]))] for _ in range(len(A))]

    for i in range(len(A)):
        for j in range(len(B[0])):
            for k in range(len(B)):
                result[i][j] += A[i][k] * B[k][j]

    return result

def matrix_add(A,B):
    if len(A)!=len(B):
        return None
    for i in range(len(A)):
        for j in range(len(A[0])):
            A[i][j]+=B[i][j]
    return A

def matrix_div(A,B):
    if isinstance(B,float) or isinstance(B,int):
        for i in range(len(A)):
            for j in range(len(A[0])):
                A[i][j]/=B
    elif len(A)==len(B) and len(A[0])==len(B[0]):
        for i in range(len(A)):
            for j in range(len(A[0])):
                A[i][j]/=B[i][j]
    else:
        print(f"invalid matrices:\n{A=}\n{B=}")

class NeuralNet:
        def __init__(self,layers,weights=None,biases=None,activation="Threshold"):
            '''Doesnt have a backprop function since it'll be trained using genetic algorithm'''
            self.weights=[]
            self.biases=[]
            self.e=2.71828
            self.activation=self.ReLu
            if activation == "Sigmoid":
                self.activation=self.Sigmoid
            elif activation == "Threshold":
                self.activation=self.Threshold
            if weights!=None and biases!=None:
                self.weights=weights
                self.biases=biases
            else:
                #8 10 3
                #1x8 8x10 1x10 10x3
                for i in range(len(layers)-1):
                    self.biases.append([[random()*2-1 for x in range(layers[i+1])]])
                    weight=[]
                    for j in range(layers[i]):
                        weight.append([random()*2-1 for x in range(layers[i+1])])
                    self.weights.append(weight)
              
        def ReLu(self,input):
            result=[]
            for i in input:
                if i[0] >0:
                    result.append(i[0])
                else:
                    result.append(0)
            return result
        
        def Sigmoid(self,input):
            result=[]
            for i in input:
                temp=1/(1+pow(self.e,-i[0]))
                result.append(temp)
            return result
        
        def Threshold(self,input):

            return [[int(x>0) for x in input[0]]]

        def forward(self,inputs):
            result=inputs
            
            for i in range(len(self.weights)):

                result=matrix_multiply(result,self.weights[i]  )
                result=matrix_add(result,self.biases[i])
                result=self.activation(result)
            return result
            
        def save(self):
            pass
        def load(self):
            pass

def checkCollision(obj1,obj2):
        distance=pow(pow(obj1.pos[0]-obj2.pos[0],2)+pow(obj1.pos[1]-obj2.pos[1],2),.5)
        # print(f"{distance=}")
        if distance <= obj1.radius+obj2.radius:
            return True
        return False

spid=0
class SpaceShip:
    def __init__(self,pos,radius,sprite,direction=0):
        global spid
        self.id=spid
        spid+=1
        self.isAlive=True
        self.hp=100
        self.maxSpeed=50
        self.speed=[0,0]
        self.accel=70
        self.angularVel=0
        self.angularAccel=240
        self.pos=pos
        self.direction=direction
        self.radius=radius
        self.sprite=sprite
        self.time=0
        self.shootTimer=0
        # self.cube=scene.add_cube(newId(),self.radius, self.pos[0],self.pos[1],64, 0,0,0, 1,1,0.01)
        # image.set_texture(self.cube,self.sprite)
    
    def update(self,inputs):
        # deltaT=time.time()-self.time
        # self.time=time.time()
        # if deltaT>0.1:
        #     deltaT=0.1
        deltaT=0.0167
        self.time+=deltaT
        self.shootTimer+=deltaT

        self.angularVel-=inputs[1]*deltaT*self.angularAccel/2
        self.direction+=self.angularVel*deltaT
        self.direction%=360

        self.speed[0]+=inputs[0]*cos(radians(self.direction+90))*deltaT*self.accel/2
        self.speed[1]+=inputs[0]*sin(radians(self.direction+90))*deltaT*self.accel/2
        
        self.pos[0]+=self.speed[0]*deltaT
        self.pos[1]+=self.speed[1]*deltaT
        # scene.rotation(self.cube,0,0,self.direction)
        # scene.setPosition(self.cube,0,self.pos[0],self.pos[1],64)

        if inputs[2]:
            if self.shootTimer > 0.2:
                self.shootTimer=0
                return Bullet(copy.copy(self.id),copy.copy(self.pos),copy.copy(radians(self.direction+90)),copy.copy(self.speed))

    def damage(self,damage):
        self.hp-=damage
        # print(self.hp)
        if self.hp <=0:
            self.isAlive=False
        

class AlienShip(SpaceShip):
    def __init__(self,*args,**kwargs):
        SpaceShip.__init__(self,*args)
        self.genes=kwargs["genes"]
        self.scores=[]
        self.score=0
        self.timeinit=0
        self.damageDone=0
        if self.genes==None:
            self.nn=NeuralNet(layers=[14,20,20,3])
            self.genes=[self.nn.weights,self.nn.biases]
        else:
            self.nn=NeuralNet(layers=[14,20,20,3],weights=self.genes[0],biases=self.genes[1])
        
    
    def updateNN(self,inputs):
        if self.isAlive:
            self.timeinit+=0.0167
            inputs=self.nn.forward(inputs)
            self.score=-10*(self.timeinit) + self.hp + self.damageDone*10
            actualInputs=[inputs[0][0]*2-1,inputs[0][1]*2-1,inputs[0][2]]
            # print(inputs,actualInputs)
            return self.update(actualInputs)
        
        else:
            # scene.setPosition(self.cube,0,999,999,64)
            self.angularVel=0
            self.speed=[0,0]
    
    def clearScore(self):
        self.score=0
        self.timeinit=0
        self.damageDone=0
        self.hp=100
        self.isAlive=True
        self.pos=[randint(-50,50),randint(-30,30)]
        self.speed=[0,0]
        self.angularVel=0
        self.direction=randint(-180,180)
    
    def save(self,citer):
        if not os.path.exists("params"):
            os.mkdir("params")
        with open("params/"+str(self.id)+"_"+str(int(self.score))+"_"+str(citer)+".json", 'w') as jf:
            json.dump({"weights":self.genes[0],"biases":self.genes[1]},jf)

    def load(self,fp):
        with open(fp,'r') as jf:
            temp=json.load(jf)
            self.genes[0]=temp["weights"]
            self.genes[1]=temp["biases"]

class Bullet:
    def __init__(self,spid,pos,dir,ssSpeed):
        # print("kaboom")
        self.id=spid
        self.pos=pos
        self.direction=dir
        self.ssSpeed=ssSpeed
        self.speed=80
        self.radius=2
        self.damage=10
        self.initTime=time.time()
        self.isAlive=True
        self.time=0
        # self.cube=scene.add_cube(newId(),self.radius,self.pos[0],self.pos[1],64, 0,0,0, 1,1,0.01)
        # scene.rotation(self.cube,0,0,self.direction)


    def update(self):
        # deltaT=time.time()-self.initTime
        # self.initTime=time.time()
        deltaT=0.0167
        self.time+=deltaT
        
        x=deltaT*self.speed
        x1=deltaT*self.ssSpeed[0]
        y1=deltaT*self.ssSpeed[1]

        self.pos[0]+= cos(self.direction)*x
        self.pos[1]+= sin(self.direction)*x

        self.pos[0]+= x1
        self.pos[1]+= y1
        
        # scene.setPosition(self.cube,0,self.pos[0],self.pos[1],64)

        if self.time>3:
            self.isAlive=False

# spritePaths=[os.listdir("../media/spaceShips")]

# sprites=[image.load_texture("../media/spaceShips/"+spritePaths[0][i]) for i in range(len(spritePaths))]
sprites=[None for i in range(5)]

class Genetic:
    def __init__(self,iterations,population,mutationRate,mutationStrength,crossoverRate,elitism=3) :
        self.iterations=iterations
        self.population=population
        self.mutationRate=mutationRate
        self.crossoverRate=crossoverRate
        self.elitism=elitism
        self.mutationStrenght=mutationStrength
        self.currentIter=0
        self.individuals=[AlienShip([randint(-50,50),randint(-30,30)],10,sprites[randint(0,len(sprites)-1)],randint(-180,180),genes=None) for i in range(self.population)]

    def iterate(self):
        if self.currentIter>=self.iterations:
            for ind in self.individuals:
                ind.save(self.currentIter)
            return False
        elif self.currentIter%100 == 0:
            for ind in self.individuals:
                ind.save(self.currentIter)
        self.currentIter+=1
        self.individuals.sort(reverse=True,key= lambda a : a.score)
        print(f"top 3 scores:{[x.score for x in self.individuals[:3]]}")
        print(len(self.individuals))
        newPopulation=self.individuals[:self.elitism]
        firstHalf=self.individuals[3:len(self.individuals)//2]
        secondHalf=self.individuals[len(self.individuals)//2:]

        for i in range(len(firstHalf)):
            if random()<self.crossoverRate:
                firstHalf[i]=None
        
        for i in range(len(secondHalf)):
            if random()>self.crossoverRate:
                secondHalf[i]=None
        
        newPopulation+=firstHalf
        newPopulation+=secondHalf
        

        nonNone=[i for i in newPopulation if i is not None]


        for j in range(len(newPopulation)):
            if newPopulation[j] is None:
                rand=randint(2,5)
                parents=[]
                for i in range(rand):
                    parents.append(choice(nonNone))

                newPopulation[j]=self.crossover(copy.deepcopy(parents))
        
        for i in range(3,len(newPopulation)):
            if random()<self.mutationRate:
                newPopulation[i]=self.mutate(copy.deepcopy(newPopulation[i]))

        for ind in newPopulation:
            ind.clearScore()
            ind.scores.clear()

        return True



    def mutate(self,individual):

        newGenes=individual.genes
        weightCount=len(individual.genes[0])
        biasCount=len(individual.genes[1])
        for i in range(weightCount):
            shape=[len(newGenes[0][i]),len(newGenes[0][i][0])]
            mutations=[]
            for x in range(shape[0]):
                ys=[]
                for y in range(shape[1]):
                    if random() < self.mutationRate:
                        ys.append(gaussianRandom(self.mutationStrenght,10,-self.mutationStrenght/2))
                    else:
                        ys.append(0)
                mutations.append(ys)

            matrix_add(newGenes[0][i],mutations)

            
        for i in range(biasCount):
            shape=[len(newGenes[1][i]),len(newGenes[1][i][0])]
            mutations=[]
            for x in range(shape[0]):
                ys=[]
                for y in range(shape[1]):
                    if random() < self.mutationRate:
                        ys.append(gaussianRandom(self.mutationStrenght,10,-self.mutationStrenght/2))
                    else:
                        ys.append(0)
                mutations.append(ys)


            matrix_add(newGenes[1][i],mutations)

            
            
        individual.genes=newGenes
        return individual


    def crossover(self,individuals):
        newGenes=individuals[0].genes
        weightCount=len(individuals[0].genes[0])
        biasCount=len(individuals[0].genes[1])
        for i in range(1,weightCount):
            for ind in individuals[1:]:
                matrix_add(newGenes[0][i],ind.genes[0][i])
            matrix_div(newGenes[0][i],len(individuals))
        for i in range(1,biasCount):
            for ind in individuals[1:]:
                matrix_add(newGenes[1][i],ind.genes[1][i])
            matrix_div(newGenes[1][i],len(individuals))
        individuals[0].genes=newGenes
        return individuals[0]

genetic=Genetic(1000,16,0.1,0.5,0.35,3)
running=True
populationAlive=True


def custSigmoid(x,b=0):
    return 1/(1+pow(2.71828,-x+b))

def duel(ai1,ai2):
    bullets=[]
    initTime=0
    while ai1.isAlive and ai2.isAlive:
        initTime+=0.0167
        if initTime>=5:
            if random()<0.5:
                ai1.isAlive=False
            else:
                ai2.isAlive=False
            break
        dists=[]
        direction=atan2(ai1.speed[0],ai1.speed[1])
        magn=custSigmoid(distance(ai1.speed[0],ai1.speed[1]),5.5)
        inputData=[custSigmoid(ai1.pos[0]),custSigmoid(ai1.pos[1]),radians(ai1.direction)/PI,radians(ai1.angularVel)/PI,direction,magn]
        for bullet in bullets:
            if bullet.id!=ai1.id:
                dists.append(distance(ai1.pos,bullet.pos))
        
        dists.sort(key=lambda a : a[2])
        if len(dists)>0:
            for i in range(2):
                if i<len(dists):
                    inputData+=[custSigmoid(dists[0][0]/320),custSigmoid(dists[0][1]/180)]
                else:
                    inputData+=[0,0]
        else:
            inputData+=[0,0,0,0]
        direction=atan2(ai1.pos[0]-ai2.pos[0],ai1.pos[1]-ai2.pos[1])
        magn=custSigmoid(distance(ai1.pos,ai2.pos)[2],5.5)
        inputData+= [direction/PI,custSigmoid(magn,5.5),radians(ai2.direction)/PI,radians(ai2.angularVel)/PI]

        dists=[]
        direction=atan2(ai2.speed[0],ai2.speed[1])
        magn=custSigmoid(distance(ai2.speed[0],ai2.speed[1]),5.5)
        inputData1=[custSigmoid(ai2.pos[0]),custSigmoid(ai2.pos[1]),radians(ai2.direction)/PI,radians(ai2.angularVel)/PI,direction,magn]
        for bullet in bullets:
            if bullet.id!=ai2.id:
                dists.append(distance(ai2.pos,bullet.pos))
        dists.sort(key=lambda a : a[2])
        if len(dists)>0:
            for i in range(2):
                if i<len(dists):
                    inputData1+=[custSigmoid(dists[0][0]/320),custSigmoid(dists[0][1]/180)]
                else:
                    inputData1+=[0,0]
        else:
            inputData1+=[0,0,0,0]
        direction=atan2(ai2.pos[0]-ai1.pos[0],ai2.pos[1]-ai1.pos[1])
        magn=custSigmoid(distance(ai2.pos,ai1.pos)[2],5.5)
        inputData1+= [direction/PI,custSigmoid(magn,5.5),radians(ai1.direction)/PI,radians(ai1.angularVel)/PI]

        temp=ai1.updateNN([inputData])
        if temp is not None:
            bullets.append(temp)
        temp=ai2.updateNN([inputData1])
        if temp is not None:
            bullets.append(temp)
        
        sch=[]  
        for i in range(len(bullets)):
            bullets[i].update()
            # pg.draw.circle(screen,(255,50,50),[bullets[i].pos[0]+640,bullets[i].pos[1]+360],10)
            # if checkCollision(player,bullets[i]):
            #     player.damage(bullets[i].damage)
            #     bullets[i].isAlive=False
            indct=0
            for individual in [ai1,ai2]:
                if checkCollision(individual,bullets[i]) and individual.id!=bullets[i].id:
                    individual.damage(bullets[i].damage)
                    bullets[i].isAlive=False
                    if indct==0:
                        ai2.damageDone+=20
                    else:
                        ai1.damageDone+=20
                indct+=1


            if not bullets[i].isAlive:
                sch.append(i)

        sch=list(set(sch))
        sch.sort(reverse=True)
        for i in sch:
            bullets.pop(i)
    return ai1.isAlive,ai1.score,ai2.isAlive,ai2.score

def tournament(geneticObj):
    indices=[[i,True] for i in range(len(geneticObj.individuals))]
    
    while len(indices)>1:
        print(len(indices))
        pool = ThreadPool(processes=len(indices)//2)
        duelResults=[]
        for i in range(len(indices)//2):
            duelResults.append(pool.apply_async(duel,(geneticObj.individuals[i],geneticObj.individuals[len(indices)-1-i])))
        i=0
        for thr in duelResults:
            val=thr.get()
            indices[i][1]=val[0]
            geneticObj.individuals[i].clearScore()
            geneticObj.individuals[i].scores.append(val[1])
            indices[len(indices)-1-i][1]=val[2]
            geneticObj.individuals[len(indices)-1-i].clearScore()
            geneticObj.individuals[len(indices)-1-i].scores.append(val[3])
            i+=1
        
        indices=[i for i in indices if i[1]]
    for i in range(len(geneticObj.individuals)):
        geneticObj.individuals[i].score+=sum(geneticObj.individuals[i].scores)
    return geneticObj.iterate(),geneticObj


if train:
    running=True
    while running:
        running,genetic=tournament(genetic)
        if genetic.currentIter%10==0:
            print(genetic.currentIter)
else:
    pg.init()
    screen = pg.display.set_mode((1280, 720))
    clock = pg.time.Clock()
    running = True
    if os.path.exists("params"):
        with open("params/7_1940_1000.json" , 'r') as jfl:
            genes=json.load(jfl)
            genes=[genes["weights"],genes["biases"]]
    else:
        raise Exception("no parameters found")
    ai1=AlienShip([-50,0],10,None,0,genes=genes)
    ai2=AlienShip([50,0],10,None,0,genes=genes)
    bullets=[]
    while running:
        start=time.time()
        # poll for events
        # pygame.QUIT event means the user clicked X to close your window
        for event in pg.event.get():
            if event.type == pg.QUIT:
                running = False

        # fill the screen with a color to wipe away anything from last frame
        screen.fill("white")
        # if len(bullets)>0:
        #     print(bullets[0].pos)
        ############## input for first ai
        dists=[]
        direction=atan2(ai1.speed[0],ai1.speed[1])
        magn=custSigmoid(distance(ai1.speed[0],ai1.speed[1]),5.5)
        inputData=[custSigmoid(ai1.pos[0]),custSigmoid(ai1.pos[1]),radians(ai1.direction)/PI,radians(ai1.angularVel)/PI,direction,magn]
        for bullet in bullets:
            if bullet.id!=ai1.id:
                dists.append(distance(ai1.pos,bullet.pos))
        
        dists.sort(key=lambda a : a[2])
        if len(dists)>0:
            for i in range(2):
                if i<len(dists):
                    inputData+=[custSigmoid(dists[0][0]/320),custSigmoid(dists[0][1]/180)]
                else:
                    inputData+=[0,0]
        else:
            inputData+=[0,0,0,0]
        direction=atan2(ai1.pos[0]-ai2.pos[0],ai1.pos[1]-ai2.pos[1])
        magn=custSigmoid(distance(ai1.pos,ai2.pos)[2],5.5)
        inputData+= [direction/PI,custSigmoid(magn,5.5),radians(ai2.direction)/PI,radians(ai2.angularVel)/PI]

        dists=[]
        direction=atan2(ai2.speed[0],ai2.speed[1])
        magn=custSigmoid(distance(ai2.speed[0],ai2.speed[1]),5.5)
        inputData1=[custSigmoid(ai2.pos[0]),custSigmoid(ai2.pos[1]),radians(ai2.direction)/PI,radians(ai2.angularVel)/PI,direction,magn]
        for bullet in bullets:
            if bullet.id!=ai2.id:
                dists.append(distance(ai2.pos,bullet.pos))
        dists.sort(key=lambda a : a[2])
        if len(dists)>0:
            for i in range(2):
                if i<len(dists):
                    inputData1+=[custSigmoid(dists[0][0]/320),custSigmoid(dists[0][1]/180)]
                else:
                    inputData1+=[0,0]
        else:
            inputData1+=[0,0,0,0]
        direction=atan2(ai2.pos[0]-ai1.pos[0],ai2.pos[1]-ai1.pos[1])
        magn=custSigmoid(distance(ai2.pos,ai1.pos)[2],5.5)
        inputData1+= [direction/PI,custSigmoid(magn,5.5),radians(ai1.direction)/PI,radians(ai1.angularVel)/PI]

        temp=ai1.updateNN([inputData])
        if temp is not None:
            bullets.append(temp)
        temp=ai2.updateNN([inputData1])
        if temp is not None:
            bullets.append(temp)
        
        print(ai1.pos)
        sch=[]  
        for i in range(len(bullets)):
            bullets[i].update()
            pg.draw.circle(screen,(255,50,50),[bullets[i].pos[0]+640,bullets[i].pos[1]+360],10)
            # if checkCollision(player,bullets[i]):
            #     player.damage(bullets[i].damage)
            #     bullets[i].isAlive=False
            indct=0
            for individual in [ai1,ai2]:
                if checkCollision(individual,bullets[i]) and individual.id!=bullets[i].id:
                    individual.damage(bullets[i].damage)
                    bullets[i].isAlive=False
                    if indct==0:
                        ai2.damageDone+=20
                    else:
                        ai1.damageDone+=20
                indct+=1


            if not bullets[i].isAlive:
                sch.append(i)

        sch=list(set(sch))
        sch.sort(reverse=True)
        for i in sch:
            bullets.pop(i)
        # print(ai1.speed)
        pg.draw.circle(screen,(50,255,50),[ai1.pos[0]+640,ai1.pos[1]+360],ai1.radius)
        pg.draw.circle(screen,(50,50,255),[ai2.pos[0]+640,ai2.pos[1]+360],ai2.radius)
        # RENDER YOUR GAME HERE

        # flip() the display to put your work on screen
        pg.display.flip()

        clock.tick(60)  # limits FPS to 60
        delta=time.time()-start
        if delta<1/60:
            time.sleep(1/60-delta)

    pg.quit()
