import sys
import random
import math
import matplotlib.pyplot as plt
import time
import fitness

attributes_sizes = [4, 8, 3, 16, 3, 7, 14, 6, 5, 2, 2, 2, 4, 41, 1]
attributes_qty = 15
genes_qty = 118

class Hypotheses:

    def __init__(self, chromosome, chromosome_size):
        self.chromosome = chromosome
        self.fitness = -1
        self.chromosome_size = chromosome_size
        
    def gabilCrossover(self, couple):
        point1 = random.randrange(0, len(self.chromosome))        
        point2 = random.randrange(0, len(self.chromosome))
        while point1 == point2:
            point2 = random.randrange(0, len(self.chromosome))
        
        if point2 < point1:
            aux = point1
            point1 = point2
            point2 = aux

        num_chromosomes = len(self.chromosome) // self.chromosome_size
        #print num_chromosomes
        
        d1 = point1 - ((point1 // self.chromosome_size) * self.chromosome_size)
        d2 = point2 - ((point2 // self.chromosome_size) * self.chromosome_size)

        while d1 > d2:
            point1 = random.randrange(0, len(self.chromosome))        
            point2 = random.randrange(0, len(self.chromosome))
            while point1 == point2:
                point2 = random.randrange(0, len(self.chromosome))
        
            if point2 < point1:
                aux = point1
                point1 = point2
                point2 = aux

            num_chromosomes = len(self.chromosome) // self.chromosome_size
            
        
            d1 = point1 - ((point1 // self.chromosome_size) * self.chromosome_size)
            d2 = point2 - ((point2 // self.chromosome_size) * self.chromosome_size)

        #print d1
        #print d2

        couple_num_chromosomes = len(couple.chromosome) // couple.chromosome_size
        couple_point1s = []
        couple_point2s = []

        for i in range(0, couple_num_chromosomes):
            couple_point1s.append((i * couple.chromosome_size) + d1)
            couple_point2s.append((i * couple.chromosome_size) + d2)

        possible_couple_points = []
        for fst_p in couple_point1s:
            for lst_p in couple_point2s:
                if lst_p >= fst_p:
                    possible_couple_points.append((fst_p, lst_p))

        choice = random.randrange(0, len(possible_couple_points))
        #print choice

        child1 = self.chromosome[0:point1] + couple.chromosome[possible_couple_points[choice][0]:possible_couple_points[choice][1]] + self.chromosome[point2:]
        child2 = couple.chromosome[0:possible_couple_points[choice][0]] + self.chromosome[point1:point2] + couple.chromosome[possible_couple_points[choice][1]:]

        return [Hypotheses(child1, 118), Hypotheses(child2, 118)]

    def onePointCrossover(self, couple):
        d1 = random.randrange(0, len(self.chromosome))
        #print d1
        d2_options = [d1]
        dot = d1
        while True:
            dot -= genes_qty
            if dot >= 0: d2_options.append(dot)
            else: break
        dot = d1
        while True:
            dot += genes_qty
            if dot < len(self.chromosome): d2_options.append(dot)
            else: break
        #print d2_options
        d2 = random.choice(d2_options)
        #print d2

        child1 = self.chromosome[0:d1] + couple.chromosome[d2:]
        child2 = couple.chromosome[0:d2] + self.chromosome[d1:]

        return [Hypotheses(child1, 118), Hypotheses(child2, 118)]

    def mutate(self, position):
        if self.chromosome[position] == 0:
            self.chromosome[position] = 1
        else:
            self.chromosome[position] = 0

                
    def accedAttb(self, pos_attb):
        if pos_attb >= attributes_qty or pos_attb < 0:
            print "Acceso Incorrecto a los Atributos"
        else:
            len_attrb = attributes_sizes[pos_attb]
            shift = sum(attributes_sizes[0:pos_attb])
            return (shift,shift+len_attrb)

    def AA_DC(self, flag):
        attb_sel = random.randrange(0,attributes_qty)
        chrom_sel = random.randrange(0,len(self.chromosome) // genes_qty)
        attb_pos = self.accedAttb(attb_sel)
        for i in range(attb_pos[0] + genes_qty*chrom_sel,attb_pos[1] + genes_qty*chrom_sel):
            if self.chromosome[i] == 0:
                self.chromosome[i] = 1
                if flag: break

def crossover(generation, gen_size, crossover_rate):
    sum_fitness = sum(map(retFitness, generation))
    prob_generation = []
    final_gen = []

    selected = 0
    while selected < (crossover_rate * gen_size):
        for g in generation:
            if sum_fitness == 0:                    
                prob = 0
            else:
                prob = g.fitness / sum_fitness                
            num = random.random()
            if num > prob:
                final_gen.append(g)
                selected += 1
            if selected == (crossover_rate * gen_size):
                break
    
    children = []

    i = 0
    while i < len(final_gen):
        children += final_gen[i].gabilCrossover(final_gen[i+1])
        i += 2

    return children
                    
def chooseMutationHypotheses(mutation_rate, gen_size, parents, children, test_data):
    number_of_mutations = int(round((mutation_rate * gen_size)))
                                
    for i in range(0, number_of_mutations):
        choice = random.randrange(0, gen_size)
        if choice < len(parents):            
            mutation_bit = random.randrange(0, len(parents[choice].chromosome))
            parents[choice].mutate(mutation_bit)
            new_parent_fit = fitness.computeFitness(test_data, [parents[choice].chromosome])
            parents[choice].fitness = new_parent_fit[0]
        else:
            mutation_bit = random.randrange(0, len(children[len(children) - choice].chromosome))
            children[len(children) - choice].mutate(mutation_bit)

def retFitness(chromosome):
    return chromosome.fitness

def chromosome(hyp):
    return hyp.chromosome

def ratio(chromosome, sum_fitness):
        return float(chromosome.fitness) / float(sum_fitness)

def setPopulationRatio(population,sum_fitness):
    sum_fitness_vector = []
    for i in range(0, len(population)):
        sum_fitness_vector.append(sum_fitness)
    if sum_fitness == 0:
        out = []
        prom = float(len(population)) / float(100)
        for i in range(0,len(population)):
            out.append(prom)
        return out
    else: 
        return map(ratio,population, sum_fitness_vector)

def setPosition(fitnessRatioPop):
    pop = []
    for i in range(0,len(fitnessRatioPop)):
        pop.append([i,fitnessRatioPop[i]])
    return pop

def compare(a, b):
    if a[1] > b[1]:
        return 1
    elif a[1] == b[1]:
        return 0
    else: # a[1] < b[1]:
        return -1

def compareFitness(a, b):
    if a.fitness > b.fitness:
        return 1
    elif a.fitness == b.fitness:
        return 0
    else:
        return -1

def setRanges(pop):
    pop_aux = pop
    for i in range(1,len(pop)):
        pop_aux[i][1] = pop[i][1]+pop[i-1][1]
    return pop_aux

def selection(population,typeSelection,selection_rate, crossover_rate):

    sum_fitness = sum(map(retFitness, population))
    fitnessRatioPop = setPopulationRatio(population,sum_fitness)
    pop_aux = setPosition(fitnessRatioPop)
    pop_aux.sort(compare)
    new_pop = []
    qty = 0

    if typeSelection == 1:
        
        #Seleccion por ruleta
        pop_aux2 = setRanges(pop_aux)
        for i in range(0, int(selection_rate)):
            roulette = random.random()
            for j in range(0, len(pop_aux2)):
                if roulette <= pop_aux2[j][1]:
                    new_pop.append(population[pop_aux2[j][0]])
                    break
    
        return new_pop

    elif typeSelection == 2:

        #Seleccion por probabilidad
        prob = 0
        num_sel = selection_rate#int((1 - crossover_rate)*selection_rate)
        while qty < num_sel:
            for i in range(0, len(population)):
                if sum_fitness == 0:                    
                    prob = 0
                else:
                    prob = retFitness(population[i]) / sum_fitness                    
                num = random.random()
                if num < prob:
                    new_pop.append(population[i])
                    qty += 1
                if qty == num_sel: break
        return new_pop

    elif typeSelection == 3:

        #Seleccion de los mejores
        for i in range (0, len(pop_aux)):
                new_pop.append(population[pop_aux[len(pop_aux) - i -1][0]])
                qty += 1
                if qty == selection_rate: break
        return new_pop
        

# DATA:
# [0,4]   - 0 Age: (4) continuous.
# [4,12]  - 1 Workclass: (8) Private, Self-emp-not-inc, Self-emp-inc, Federal-gov, Local-gov, State-gov, Without-pay, Never-worked.
# [12,15] - 2 Fnlwgt: (3) continuous.
# [15,31] - 3 Education: (16) Bachelors, Some-college, 11th, HS-grad, Prof-school, Assoc-acdm, Assoc-voc, 9th, 7th-8th, 12th, Masters, 1st-4th, 10th, Doctorate, 5th-6th, Preschool.
# [31,34] - 4 Education-num: (3) continuous.
# [34,41] - 5 Marital-status: (7) Married-civ-spouse, Divorced, Never-married, Separated, Widowed, Married-spouse-absent, Married-AF-spouse.
# [41,55] - 6 Occupation: (14) Tech-support, Craft-repair, Other-service, Sales, Exec-managerial, Prof-specialty, Handlers-cleaners, Machine-op-inspct, Adm-clerical, Farming-fishing, Transport-moving, Priv-house-serv, Protective-serv, Armed-Forces.
# [55,61] - 7 Relationship: (6) Wife, Own-child, Husband, Not-in-family, Other-relative, Unmarried.
# [61,66] - 8 Race: (5) White, Asian-Pac-Islander, Amer-Indian-Eskimo, Other, Black.
# [66,68] - 9 Sex: (2) Female, Male.
# [68,70] - 10 Capital-gain: (2) continuous.
# [70,72] - 11 Capital-loss: (2) continuous.
# [72,76] - 12 Hours-per-week: (4) continuous.
# [76,117] - 13 Native-country: (41) United-States, Cambodia, England, Puerto-Rico, Canada, Germany, Outlying-US(Guam-USVI-etc), India, Japan, Greece, South, China, Cuba, Iran, Honduras, Philippines, Italy, Poland, Jamaica, Vietnam, Mexico, Portugal, Ireland, France, Dominican-Republic, Laos, Ecuador, Taiwan, Haiti, Columbia, Hungary, Guatemala, Nicaragua, Scotland, Thailand, Yugoslavia, El-Salvador, Trinadad&Tobago, Peru, Hong, Holand-Netherlands.
# [117] - 14 Sallary: (2) >50K, <=50K.

def readData(filename):    
    data = []
    file = open(filename,'r')
    while True:
        line = file.readline()
        if not line: break
        line_content = line.split()
        data.append(line_content)
    file.close()
    return data

def translateAgeData(h):
    age = []
    option = -2

    # Age
    if h[0] == '?':
        option = -1
    elif 17 <= int(h[0]) < 32:
        option = 0
    elif 32 <= int(h[0]) < 46:
        option = 1
    elif 46 <= int(h[0]) < 68:
        option = 2
    elif 68 <= int(h[0]) <= 90:
        option = 3

    if option != -1:
        for i in range(0, 4):
            if i == option:
                age.append(1)
            else:
                age.append(0)
    else:
        age = [1] * 4

    return age

def translateWorkclassData(h):
    workclass = []
    option = -2

    # Workclass
    if h[1] == 'Private':
        option = 0
    elif h[1] == 'Self-emp-not-inc':        
        option = 1
    elif h[1] == 'Self-emp-inc':
        option = 2
    elif h[1] == 'Federal-gov':
        option = 3
    elif h[1] == 'Local-gov':
        option = 4
    elif h[1] == 'State-gov':
        option = 5
    elif h[1] == 'Without-pay':
        option = 6
    elif h[1] == 'Never-worked':
        option = 7
    elif h[1] == '?':
        option = -1

    if option != -1:
        for i in range(0, 8):
            if i == option:
                workclass.append(1)
            else:
                workclass.append(0)
    else:
        workclass = [1] * 8

    return workclass

def translateFnlwgtData(h):
    fnlwgt = []
    option = -2

    if h[2] == '?':
        option = -1
    if 12285 <= int(h[2]) < 150000:
        option = 0
    elif 150000 <= int(h[2]) < 300000:
        option = 1
    elif 300000 <= int(h[2]) <= 1484705:
        option = 2

    if option != -1:
        for i in range(0, 3):
            if i == option:
                fnlwgt.append(1)
            else:
                fnlwgt.append(0)
    else:
        fnlwgt = [1] * 3

    return fnlwgt

def translateEducationData(h):
    education = []
    option = -2
    
    if h[3] == 'Bachelors':
        option = 0
    elif h[3] == 'Some-college':
        option = 1
    elif h[3] == '11th':
        option = 2
    elif h[3] == 'HS-grad':
        option = 3
    elif h[3] == 'Prof-school':
        option = 4
    elif h[3] == 'Assoc-acdm':
        option = 5
    elif h[3] == 'Assoc-voc':
        option = 6
    elif h[3] == '9th':
        option = 7
    elif h[3] == '7th-8th':
        option = 8
    elif h[3] == '12th':
        option = 9
    elif h[3] == 'Masters':
        option = 10
    elif h[3] == '1st-4th':
        option = 11
    elif h[3] == '10th':
        option = 12
    elif h[3] == 'Doctorate':
        option = 13
    elif h[3] == '5th-6th':
        option = 14
    elif h[3] == 'Preschool':
        option = 15
    elif h[3] == '?':
        option = -1

    if option != -1:
        for i in range(0, 16):
            if i == option:
                education.append(1)
            else:
                education.append(0)
    else:
        education = [1] * 16

    return education

def translateEducNumData(h):
    educ_num = []
    option = -2

    if h[4] == '?':
        option = -1
    elif 1 <= int(h[4]) < 9:
        option = 0
    elif 9 <= int(h[4]) < 12:
        option = 1
    elif 12 <= int(h[4]) <= 16:
        option = 2

    if option != -1:
        for i in range(0, 3):
            if i == option:
                educ_num.append(1)
            else:
                educ_num.append(0)
    else:
        educ_num = [1] * 3

    return educ_num

def translateMaritalStatusData(h):
    marital_status = []
    option = -2
    
    if h[5] == 'Married-civ-spouse':
        option = 0
    elif h[5] == 'Divorced':
        option = 1
    elif h[5] == 'Never-married':
        option = 2
    elif h[5] == 'Separated':
        option = 3
    elif h[5] == 'Widowed':
        option = 4
    elif h[5] == 'Married-spouse-absent':
        option = 5
    elif h[5] == 'Married-AF-spouse':
        option = 6
    elif h[5] == '?':
        option = -1

    if option != -1:
        for i in range(0, 7):
            if i == option:
                marital_status.append(1)
            else:
                marital_status.append(0)
    else:
        marital_status = [1] * 7

    return marital_status

def translateOccupationData(h):
    occupation = []
    option = -2

    if h[6] == 'Tech-support':
        option = 0
    elif h[6] == 'Craft-repair':
        option = 1
    elif h[6] == 'Other-service':
        option = 2
    elif h[6] == 'Sales':
        option = 3
    elif h[6] == 'Exec-managerial':
        option = 4
    elif h[6] == 'Prof-specialty':
        option = 5
    elif h[6] == 'Handlers-cleaners':
        option = 6
    elif h[6] == 'Machine-op-inspct':
        option = 7
    elif h[6] == 'Adm-clerical':
        option = 8
    elif h[6] == 'Farming-fishing':
        option = 9
    elif h[6] == 'Transport-moving':
        option = 10
    elif h[6] == 'Priv-house-serv':
        option = 11
    elif h[6] == 'Protective-serv':
        option = 12
    elif h[6] == 'Armed-Forces':
        option = 13
    elif h[6] == '?':
        option = -1

    if option != -1:
        for i in range(0, 14):
            if i == option:
                occupation.append(1)
            else:
                occupation.append(0)
    else:
        occupation = [1] * 14
                
    return occupation

def translateRelationshipData(h):
    relationship = []
    option = -2

    if h[7] == 'Wife':
        option = 0
    elif h[7] == 'Own-child':
        option = 1
    elif h[7] == 'Husband':
        option = 2
    elif h[7] == 'Not-in-family':
        option = 3
    elif h[7] == 'Other-relative':
        option = 4
    elif h[7] == 'Unmarried':
        option = 5
    elif h[7] == '?':
        option = -1

    if option != -1:
        for i in range(0, 6):
            if i == option:
                relationship.append(1)
            else:
                relationship.append(0)
    else:
        relationship = [1] * 6

    return relationship

def translateRaceData(h):
    race = []
    option = -2

    if h[8] == 'White':
        option = 0
    elif h[8] == 'Asian-Pac-Islander':
        option = 1
    elif h[8] == 'Amer-Indian-Eskimo':
        option = 2
    elif h[8] == 'Other':
        option = 3
    elif h[8] == 'Black':
        option = 4
    elif h[8] == '?':
        option = -1

    if option != -1:
        for i in range(0, 5):
            if i == option:
                race.append(1)
            else:
                race.append(0)
    else:
        race = [1] * 5

    return race

def translateSexData(h):
    sex = []

    if h[9] == 'Female':
        sex.append(1)
        sex.append(0)
    elif h[9] == 'Male':
        sex.append(0)
        sex.append(1)
    elif h[9] == '?':
        sex = [1] * 2

    return sex

def translateCapitalGainData(h):
    capital_gain = []

    if h[10] == '?':
        capital_gain = [1] * 2
    elif 0 <= int(h[10]) < 10000:
        capital_gain.append(1)
        capital_gain.append(0)
    elif 10000 <= int(h[10]) <= 99999:
        capital_gain.append(0)
        capital_gain.append(1)

    return capital_gain

def translateCapitalLossData(h):
    capital_loss = []

    if h[11] == '?':
        capital_loss = [1] * 2
    elif 0 <= int(h[11]) < 450:
        capital_loss.append(1)
        capital_loss.append(0)
    elif 450 <= int(h[11]) <= 4356:
        capital_loss.append(0)
        capital_loss.append(1)

    return capital_loss

def translateHoursPerWeekData(h):
    hours_per_week = []
    option = -2

    if h[12] == '?':
        option = -1
    elif 1 <= int(h[12]) < 30:
        option = 0
    elif 30 <= int(h[12]) < 40:
        option = 1
    elif 40 <= int(h[12]) < 70:
        option = 2
    elif 70 <= int(h[12]) <= 99:
        option = 3    

    if option != -1:
        for i in range(0, 4):
            if i == option:
                hours_per_week.append(1)
            else:
                hours_per_week.append(0)
    else:
        hours_per_week = [1] * 4


    return hours_per_week

def translateNativeCountryData(h):
    native_country = []
    option = -2

    if h[13] == 'United-States':
        option = 0
    elif h[13] == 'Cambodia':
        option = 1
    elif h[13] == 'England':
        option = 2
    elif h[13] == 'Puerto-Rico':
        option = 3
    elif h[13] == 'Canada':
        option = 4
    elif h[13] == 'Germany':
        option = 5
    elif h[13] == 'Outlying-US(Guam-USVI-etc)':
        option = 6
    elif h[13] == 'India':
        option = 7
    elif h[13] == 'Japan':
        option = 8
    elif h[13] == 'Greece':
        option = 9
    elif h[13] == 'South':
        option = 10
    elif h[13] == 'China':
        option = 11
    elif h[13] == 'Cuba':
        option = 12
    elif h[13] == 'Iran':
        option = 13
    elif h[13] == 'Honduras':
        option = 14
    elif h[13] == 'Philippines':
        option = 15
    elif h[13] == 'Italy':
        option = 16
    elif h[13] == 'Poland':
        option = 17
    elif h[13] == 'Jamaica':
        option = 18
    elif h[13] == 'Vietnam':
        option = 19
    elif h[13] == 'Mexico':
        option = 20
    elif h[13] == 'Portugal':
        option = 21
    elif h[13] == 'Ireland':
        option = 22
    elif h[13] == 'France':
        option = 23
    elif h[13] == 'Dominican-Republic':
        option = 24
    elif h[13] == 'Laos':
        option = 25
    elif h[13] == 'Ecuador':
        option = 26
    elif h[13] == 'Taiwan':
        option = 27
    elif h[13] == 'Haiti':
        option = 28
    elif h[13] == 'Columbia':
        option = 29
    elif h[13] == 'Hungary':
        option = 30
    elif h[13] == 'Guatemala':
        option = 31
    elif h[13] == 'Nicaragua':
        option = 32
    elif h[13] == 'Scotland':
        option = 33
    elif h[13] == 'Thailand':
        option = 34
    elif h[13] == 'Yugoslavia':
        option = 35
    elif h[13] == 'El-Salvador':
        option = 36
    elif h[13] == 'Trinadad&Tobago':
        option = 37
    elif h[13] == 'Peru':
        option = 38
    elif h[13] == 'Hong':
        option = 39
    elif h[13] == 'Holand-Netherlands':
        option = 40
    elif h[13] == '?':
        option = -1

    if option != -1:
        for i in range(0, 41):
            if i == option:
                native_country.append(1)
            else:
                native_country.append(0)
    else:
        native_country = [1] * 41

    return native_country

def translateSallaryData(h):
    sallary = []

    if h[14] == '>50K':
        sallary.append(1)
    else:
        sallary.append(0)

    return sallary

def translateTestData(data):
    test_data = []
    for h in data:
        hypotheses = []
        age = translateAgeData(h)        
        workclass = translateWorkclassData(h)
        fnlwgt = translateFnlwgtData(h)
        education = translateEducationData(h)
        educ_num = translateEducNumData(h)
        marital_status = translateMaritalStatusData(h)
        occupation = translateOccupationData(h)
        relationship = translateRelationshipData(h)
        race = translateRaceData(h)
        sex = translateSexData(h)
        capital_gain = translateCapitalGainData(h)
        capital_loss = translateCapitalLossData(h)
        hours_per_week = translateHoursPerWeekData(h)
        native_country = translateNativeCountryData(h)
        sallary = translateSallaryData(h)

        hypotheses = age + workclass + fnlwgt + education + educ_num + marital_status + occupation + relationship + race + sex + capital_gain + capital_loss + hours_per_week + native_country + sallary
        test_data.append(hypotheses)        
    
    return test_data

def logicAnd(chromosome, data, base, ini, fin):
    ## result = []

##     for i in range(ini, fin):
##         result.append(chromosome[base + i] & data[i])

    return [chromosome[base + i] & data[i] for i in range(ini, fin)]

def check_1s(result):
    try:
        result.index(1)
        return 1
    except ValueError:
        return 0

## def computeFitness(test_data, population):

##     for hypotheses in population:
        
##         num_chromosomes = len(hypotheses.chromosome) // hypotheses.chromosome_size
        
##         total_classified = 0

##         for data in test_data:
            
##             for c in range(0, num_chromosomes):
                
##                 ch = (c * hypotheses.chromosome_size)
                
##                 if (1 in logicAnd(hypotheses.chromosome, data, ch, 0, 4) and
                    
##                     1 in logicAnd(hypotheses.chromosome, data, ch, 4, 12) and

##                     1 in logicAnd(hypotheses.chromosome, data, ch, 12, 15) and

##                     1 in logicAnd(hypotheses.chromosome, data, ch, 15, 31) and

##                     1 in logicAnd(hypotheses.chromosome, data, ch, 31, 34) and

##                     1 in logicAnd(hypotheses.chromosome, data, ch, 34, 41) and

##                     1 in logicAnd(hypotheses.chromosome, data, ch, 41, 55) and

##                     1 in logicAnd(hypotheses.chromosome, data, ch, 55, 61) and

##                     1 in logicAnd(hypotheses.chromosome, data, ch, 61, 66) and

##                     1 in logicAnd(hypotheses.chromosome, data, ch, 66, 68) and

##                     1 in logicAnd(hypotheses.chromosome, data, ch, 68, 70) and

##                     1 in logicAnd(hypotheses.chromosome, data, ch, 70, 72) and

##                     1 in logicAnd(hypotheses.chromosome, data, ch, 72, 76) and
                    
##                     1 in logicAnd(hypotheses.chromosome, data, ch, 76, 117) and
                    
##                     hypotheses.chromosome[ch + 117] == data[117]):
                    
##                     total_classified += 1
                    
##                     break

##         hypotheses.fitness = ((total_classified) / float(len(test_data)))**2
    
    
##     for hypotheses in population:
##         num_chromosomes = len(hypotheses.chromosome) // hypotheses.chromosome_size
##         total_classified = 0
##         for data in test_data:
##             for c in range(0, num_chromosomes):
##                 ch = (c * hypotheses.chromosome_size)
##                 and_result = logicAnd(hypotheses.chromosome, data, ch, 0, 4)
##                 if not check_1s(and_result): #Chequeo de age
##                     and_result = logicAnd(hypotheses.chromosome, data, ch, 4, 12)
##                     if not check_1s(and_result): #Chequeo de workclass
##                         and_result = logicAnd(hypotheses.chromosome, data, ch, 12, 15)
##                         if not check_1s(and_result): #Chequeo de fnlwgt
##                             and_result = logicAnd(hypotheses.chromosome, data, ch, 15, 31)
##                             if not check_1s(and_result): #Chequeo de education
##                                 and_result = logicAnd(hypotheses.chromosome, data, ch, 31, 34)
##                                 if not check_1s(and_result): #Chequeo de educ_num
##                                     and_result = logicAnd(hypotheses.chromosome, data, ch, 34, 41)
##                                     if not check_1s(and_result): #Chequeo de marital_status
##                                         and_result = logicAnd(hypotheses.chromosome, data, ch, 41, 55)
##                                         if not check_1s(and_result): #Chequeo de occupation
##                                             and_result = logicAnd(hypotheses.chromosome, data, ch, 55, 61)
##                                             if not check_1s(and_result): #Chequeo de relationship
##                                                 and_result = logicAnd(hypotheses.chromosome, data, ch, 61, 66)
##                                                 if not check_1s(and_result): #Chequeo de race
##                                                     and_result = logicAnd(hypotheses.chromosome, data, ch, 66, 68)
##                                                     if not check_1s(and_result): #Chequeo de sex
##                                                         and_result = logicAnd(hypotheses.chromosome, data, ch, 68, 70)
##                                                         if not check_1s(and_result): #Chequeo de capital_gain
##                                                             and_result = logicAnd(hypotheses.chromosome, data, ch, 70, 72)
##                                                             if not check_1s(and_result): #Chequeo de capital_loss
##                                                                 and_result = logicAnd(hypotheses.chromosome, data, ch, 72, 76)
##                                                                 if not check_1s(and_result): #Chequeo de hours_per_week
##                                                                     and_result = logicAnd(hypotheses.chromosome, data, ch, 76, 117)
##                                                                     if not check_1s(and_result): #Chequeo de native_country
##                                                                         if hypotheses.chromosome[ch + 117] == data[117]:                                                                            
##                                                                             total_classified += 1
##                                                                             break

##         hypotheses.fitness = ((total_classified) / float(len(test_data)))**2
                                                                        
# ages      -> min = 17    max = 90,     intervalos: 17 <= age < 32          , 32 <= age < 46          , 46 <= age <= 68          , 68 <= age <= 90
# fnlwgts   -> min = 12285 max = 1484705 intervalos: 12285 <= fnlwgt < 150000, 150000 <= fnlwgt < 300000, 300000 <= fnlwgt <= 1484705
# educ_nums -> min = 1     max = 16      intervalos: 1 <= educ_num < 9       , 9 <= educ_num < 12       , 12 <= educ_num <= 16
# cap_gain  -> min = 0     max = 99999   intervalos: 0 <= cap_gain < 10000   , 10000 <= cap_gain <= 99999 
# cap_loss  -> min = 0     max = 4356    intervalos: 0 <= cap_loss < 450     , 450 <= cap_loss <= 4356  
# hpw       -> min = 1     max = 99      intervalos: 1 <= hpw < 30           , 30 <= hpw < 40           , 40 <= hpw < 70           , 70 <= hpw <= 99
def attributeMinMax(data):
    data_length = len(data)
    ages = []
    fnlwgts = []
    educ_nums = []
    cap_gain = []
    cap_loss = []
    hpw = []
    sallary = []

    for i in range(0, data_length):
        ages.append(int(data[i][0]))
        fnlwgts.append(int(data[i][2]))
        educ_nums.append(int(data[i][4]))
        cap_gain.append(int(data[i][10]))
        cap_loss.append(int(data[i][11]))
        hpw.append(int(data[i][12]))
        
        
    #print 'ages'
    plt.hist(ages)
    plt.show()

    #print 'fnlwgts'
    plt.hist(fnlwgts)
    plt.show()

    #print 'educ'
    plt.hist(educ_nums)
    plt.show()

    #print 'gain'
    plt.hist(cap_gain)
    plt.show()

    #print 'loss'
    plt.hist(cap_loss)
    plt.show()

    #print 'hpw'
    plt.hist(hpw)
    plt.show()
    
    return [(min(ages), max(ages)), (min(fnlwgts), max(fnlwgts)), (min(educ_nums), max(educ_nums)), (min(cap_gain), max(cap_gain)), (min(cap_loss), max(cap_loss)), (min(hpw), max(hpw))]

def toBin(num, bin, length):
    div = num // 2
    rest = num % 2
    if div == 0:
        bin.insert(0, rest)
    else:
        bin.insert(0, rest)
        toBin(div, bin, length)

    if len(bin) < length:
        return [0] * (length - len(bin)) + bin
    else:
        return bin

def toDec(bin):
    aux = []
    for i in range(0,len(bin)): aux.append(bin[i])
    dec = 0
    for i in range(0,len(aux)):
        x = aux.pop()
        dec += x*(2**(i))
    return dec

def generateRandomPopulation(p):
    population = []

    for i in range(0, p):
        hypotheses = []
        num_chrom = random.randrange(1, 6)
        for i in range(0, num_chrom):
            for j in range(0,len(attributes_sizes)):
                rand_attr = random.randrange(0, 2**attributes_sizes[j]-1)
                hypotheses += toBin(rand_attr, [], attributes_sizes[j])

        population.append(Hypotheses(hypotheses, 118))
    return population

def max_fitness(population):
    pop_fitness = []
    for h in population:
        pop_fitness.append(h.fitness)
    return max(pop_fitness)

def assignFitness(fitnesses, population):
    i = 0
    for i in range(i, len(population)):
        population[i].fitness = fitnesses[i]

def GA(num_it, crossover_rate, mutation_rate, population_length):
    mejores = []
    data = readData('data/adult.data')
    test_data = translateTestData(data)
    population = generateRandomPopulation(population_length)

    pop_chromosomes = map(chromosome, population)
    t1 = time.time()
    new_fitness = fitness.computeFitness(test_data, pop_chromosomes)
    assignFitness(new_fitness, population)
    print time.time() - t1
    
    it = 0
    print "listo"
    while it < num_it:
        selected = selection(population, 2, (1 - crossover_rate) * population_length, crossover_rate)
        children = crossover(population, population_length, crossover_rate)
        chooseMutationHypotheses(mutation_rate, len(selected) + len(children), selected, children, test_data)
    
        pop_chromosomes = map(chromosome, children)
        t1 = time.time()
        new_fitness = fitness.computeFitness(test_data, pop_chromosomes)
        assignFitness(new_fitness, children)
        print time.time() - t1

        population = selected + children

        for h in population:
            h.AA_DC(True)
            h.AA_DC(False)        

        #mejores.append(max(map(retFitness, population)))
        print "maximo fitness ------------------------------------ maximo: " + str(max(map(retFitness, population))) + " It = " + str(it)
        all_fitness = map(retFitness, population)
        best = max(all_fitness)
        if 0.999 <= best <= 1.0:
            best_pos = all_fitness.index(best)
            break
            
        it += 1

    print "fitnesssssss: " + str(population[best_pos].fitness)
    return population[best_pos]
    #return mejores

def graficar():
    promedios = []

    for i in range(0, 50):
        promedio = 0
        for j in range(0, 10):
            promedio += intentos[j][i]
        promedios.append(promedio/float(10))

    plt.plot(promedios)
    plt.xlabel('iteraciones')
    plt.ylabel('promedio de mejor fitness')
    plt.title('Operadores de extension AA y DC')
    plt.savefig("AA_DC.png")

def lastTest(best_hyp):
    data = readData('data/adult.test')
    test_data = translateTestData(data)

    last_result = fitness.computeFitness([best_hyp.chromosome], test_data)
    cla = 0
    no_cla = 0
    for i in range(0, len(last_result)):
        if i == 0.0: no_cla += 1
        else: cla += 1
    print "listooooooooooooooooo: " + str(last_result)
    print "Clasificados = " + str(cla)
    print "NO Clasificados = " + str(no_cla)

def main():
##     intentos = []
##     for i in range(0, 1):
##         intentos.append(GA(50, 0.8, 0.005, 20))
        
##     print intentos

    #graficar()

    best_hyp = GA(1000, 0.8, 0.005, 20)
    i = 0
    print "BestHyp = "
    while i < len(best_hyp.chromosome):
        print best_hyp.chromosome[i:i+118]
        print "\/"
        i += 118
    
    lastTest(best_hyp)

main()
