# Proyecto 7 - STRIPS - Random Blocks
#
# Juan Garcia - 05-38207
# Tamara Mendt - 05-38546

import sys
import os
import random

################################################
############# Objetos y Acciones ###############
################################################

#Objeto que representa la mesa
class Table:

    def __init__(self,towers):
        self.towers = towers

    def move_from_table(self,blockA,blockB):
        if clear(self.towers,blockA) and clear(self.towers,blockB) and (blockA != blockB) and on_table(self.towers,blockA):
            for tower in range(0,len(self.towers)):
                if blockA in self.towers[tower].blocks:
                    towerA = self.towers[tower]
                if blockB in self.towers[tower].blocks:
                    towerB = self.towers[tower]
            towerB.blocks.append(blockA)
            self.towers.remove(towerA)
            return True
        else:
            return False

    def move_to_table(self,blockA,blockB):
        if clear(self.towers,blockA) and on(self.towers,blockA,blockB):
            self.towers.append(Tower([blockA]))
            for tower in range(0,len(self.towers)):
                if (blockA in self.towers[tower].blocks) or (blockB in self.towers[tower].blocks):
                    self.towers[tower].blocks.pop()
                    return True
        else:
            return False
                    
    def move(self,blockA,blockB,blockC):
        if on(self.towers,blockA,blockB) and clear(self.towers,blockA) and clear(self.towers,blockC) and blockA != blockB and blockA != blockC and blockC != blockB:
            for tower in range(0,len(self.towers)):
                if (blockA in self.towers[tower].blocks) and (blockB in self.towers[tower].blocks):
                    towerA = self.towers[tower]
                if (blockC in self.towers[tower].blocks):
                    towerB = self.towers[tower]
            towerB.blocks.append(towerA.blocks[-1])
            towerA.blocks.remove(towerA.blocks[-1])
            return True
        else:
            return False

    def random_state(self,block_list,limit):
        action = 0
        prev_action = ""
        max_continue = 0
        while action < limit:

            #Se seleccionan los bloques y la accion a realizar aleatoriamente
            bloque1 = random.randint(0,num_blocks-1)
            bloque2 = random.randint(0,num_blocks-1)
            while bloque2 == bloque1:
                bloque2 = random.randint(0,num_blocks-1)
            bloque3 = random.randint(0,num_blocks-1)
            while bloque3 == bloque1:
                bloque3 = random.randint(0,num_blocks-1)
            function = (random.randint(0,30) % 3) + 1

        
################ Se ejecuta una accion de move_from_table ##################
############################################################################

            if function == 1:
                if max_continue < 50 and prev_action == "move_from_table("+str(blocks_list[bloque1].id)+","+str(blocks_list[bloque2].id)+")":
                    max_continue = max_continue+1
                    continue

                if self.move_from_table(blocks_list[bloque1],blocks_list[bloque2]):
                    action = action +1
                    max_continue = 0
                    #print "move_from_table("+str(blocks_list[bloque1].id)+","+str(blocks_list[bloque2].id)+")"
                    prev_action = "move_to_table("+str(blocks_list[bloque1].id)+","+str(blocks_list[bloque2].id)+")"

                else:
                    if max_continue < 50 and prev_action == "move_from_table("+str(blocks_list[bloque2].id)+","+str(blocks_list[bloque1].id)+")":
                        max_continue = max_continue+1
                        continue
                    if self.move_from_table(blocks_list[bloque2],blocks_list[bloque1]):
                        action = action +1
                        max_continue = 0
                        #print "move_from_table("+str(blocks_list[bloque2].id)+","+str(blocks_list[bloque1].id)+")"
                        prev_action = "move_to_table("+str(blocks_list[bloque2].id)+","+str(blocks_list[bloque1].id)+")"
            else:

#################Se ejecuta una accion de move_to_table ##################
##########################################################################
                
                if function == 2:

                    if max_continue < 50 and prev_action == "move_to_table("+str(blocks_list[bloque1].id)+","+str(blocks_list[bloque2].id)+")":
                        max_continue = max_continue+1
                        continue
                    if self.move_to_table(blocks_list[bloque1],blocks_list[bloque2]):
                        action = action +1
                        max_continue = 0
                        #print "move_to_table("+str(blocks_list[bloque1].id)+","+str(blocks_list[bloque2].id)+")"
                        prev_action = "move_from_table("+str(blocks_list[bloque1].id)+","+str(blocks_list[bloque2].id)+")"

                    else:
                        if max_continue < 50 and prev_action == "move_to_table("+str(blocks_list[bloque2].id)+","+str(blocks_list[bloque1].id)+")":
                            max_continue = max_continue+1
                            continue
                        if self.move_to_table(blocks_list[bloque2],blocks_list[bloque1]):
                            action = action +1
                            max_continue = 0
                            #print "move_to_table("+str(blocks_list[bloque2].id)+","+str(blocks_list[bloque1].id)+")"
                            prev_action = "move_from_table("+str(blocks_list[bloque2].id)+","+str(blocks_list[bloque1].id)+")"
                else:

################### Se ejecuta una accion de move ######################
########################################################################

                    if function == 3:

                        if max_continue < 50 and prev_action == "move("+str(blocks_list[bloque1].id)+","+str(blocks_list[bloque2].id)+","+str(blocks_list[bloque3].id)+")":
                            max_continue = max_continue+1
                            continue
                        if self.move(blocks_list[bloque1],blocks_list[bloque2],blocks_list[bloque3]):
                            action = action +1
                            max_continue = 0
                            #print "move("+str(blocks_list[bloque1].id)+","+str(blocks_list[bloque2].id)+","+str(blocks_list[bloque3].id)+")"
                            prev_action = "move("+str(blocks_list[bloque1].id)+","+str(blocks_list[bloque3].id)+","+str(blocks_list[bloque2].id)+")"

                        else:
                            if max_continue < 50 and prev_action == "move("+str(blocks_list[bloque2].id)+","+str(blocks_list[bloque1].id)+","+str(blocks_list[bloque3].id)+")":
                                max_continue = max_continue+1
                                continue
                            if self.move(blocks_list[bloque2],blocks_list[bloque1],blocks_list[bloque3]):
                                action = action +1
                                max_continue = 0
                                #print "move("+str(blocks_list[bloque2].id)+","+str(blocks_list[bloque1].id)+","+str(blocks_list[bloque3].id)+")"
                                prev_action = "move("+str(blocks_list[bloque2].id)+","+str(blocks_list[bloque3].id)+","+str(blocks_list[bloque1].id)+")"

################ Funcion que entrega el estado actual ###################
#########################################################################

    def current_state(self,block_list,name_file,flag):
        state = []
        file = open(name_file,"a")
        file.write("(:"+flag+"\n")
        if flag == "goal":
            file.write("(and\n")
        for block in range(0,len(block_list)):
            if clear(self.towers,block_list[block]):
                state.append("clear("+str(block_list[block].id)+")")
                print "clear("+str(block_list[block].id)+")"
                file.write("(clear b"+str(block_list[block].id)+")\n")
            if on_table(self.towers,block_list[block]):
                state.append("on_table("+str(block_list[block].id)+")")
                print "on_table("+str(block_list[block].id)+")"
                file.write("(on-table b"+str(block_list[block].id)+")\n")
        for block1 in range(0,len(block_list)):
            for block2 in range(0,len(block_list)):
                if on(self.towers,block_list[block1],block_list[block2]):
                    state.append("on("+str(block_list[block1].id)+","+str(block_list[block2].id)+")")
                    print "on("+str(block_list[block1].id)+","+str(block_list[block2].id)+")"
                    file.write("(on b"+str(block_list[block1].id)+" b"+str(block_list[block2].id)+")\n")
        if flag == "goal":
            file.write(")")
        file.write(")\n")
        file.close()
        return state

#Objeto que representa una torre de bloques
class Tower:

    def __init__(self,blocks):
        self.blocks = blocks

#Objeto que representa un block
class Block:

    def __init__(self,id):
        self.id = id

################################################
################### Estados ####################
################################################

# El Bloque A esta sobre el Bloque B
def on(block_world,blockA,blockB):
    for tower in range(0,len(block_world)):
        if (blockA in block_world[tower].blocks) and (blockB in block_world[tower].blocks):
            if (block_world[tower].blocks.index(blockA) == block_world[tower].blocks.index(blockB) + 1):
                return True
            else:
                return False
    return False

# El bloque esta libre
def clear(block_world,block):
    for tower in range(0,len(block_world)):
        if block in block_world[tower].blocks:
            if (block_world[tower].blocks.index(block) == block_world[tower].blocks.index(block_world[tower].blocks[-1])):
                return True
            else:
                return False
    return False

# El bloque esta sobre la mesa
def on_table(block_world,block):
    for tower in range(0,len(block_world)):
        if block in block_world[tower].blocks:
            if block_world[tower].blocks.index(block) == 0:
                return True
            else:
                return False
    return False

################################################
############## Programa Principal ##############
################################################

if len(sys.argv) != 3:
    print "\nError: Ingrese bien los parametros -- use: random_blocks <num_blocks> <num_acciones>\n"
    exit()

if  (int(sys.argv[1]) < 0) or (int(sys.argv[2]) < 0):
    print "\nError: El numero de Blocks o de Acciones deben ser positivos.\n"
    exit()

num_blocks = int(sys.argv[1])
print "\nNumero de Bloques = "+str(num_blocks)
num_actions = int(sys.argv[2])
print "Numero de Acciones = "+str(num_actions)
block_world = []
blocks_list = []

for id_block in range(1,num_blocks+1):
    bloque = Block(id_block)
    block_world.append(Tower([bloque]))
    blocks_list.append(bloque)

file = open("output","w")
file.write("(define (problem randoms-blocks-"+str(num_blocks)+")\n")
file.write("(:domain blocksworld)\n")
file.write("(:objects ")
for num in range(1,num_blocks+1):
    file.write("b"+str(num)+" ")
file.write(")\n")

file.close()
my_table = Table(block_world)
#print "\nAcciones Iniciales:\n"
my_table.random_state(blocks_list,10)
print "\nEstado Inicial:\n"
my_table.current_state(blocks_list,"output","init")
print "\nAplicando Acciones..."
#print "\nAcciones:"
my_table.random_state(blocks_list,num_actions)
print "\nEstado Final:\n"
my_table.current_state(blocks_list,"output","goal")
print "\nListo...\n"
file = open("output","a")
file.write(")\n")
file.close()

