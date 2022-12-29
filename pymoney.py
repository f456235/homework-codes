#!/usr/bin/env python
# coding: utf-8

# In[ ]:





# In[ ]:


import sys
import os
class Record:
    """Represent a record."""
    def __init__ (self,category,amount,year,month,day):
        """set record's attributes"""
        self._category = category
        self._amount = amount
        self._year = year
        self._month = month
        self._day = day
    def __repr__(self):
        """print a record"""
        return (f'{self._category} {self._amount} {self._year}/{self._month}/{self._day}')
    def get_category(self):
        """get attribute'category'"""
        return self._category
    def get_amount(self):
        """get attribute'amount'"""
        return self._amount
    def get_year(self):
        """get attribute'year'"""
        return self._year
    def get_month(self):
        """get attribute'month'"""
        return self._month
    def get_day(self):
        """get attribute'day'"""
        return self._day
    category = property(lambda self: self.get_category())
    amount = property(lambda self: self.get_amount())
    year = property(lambda self: self.get_year())
    month = property(lambda self: self.get_month())
    day = property(lambda self: self.get_day())
class Records:
    """Maintain a list of all the 'Record's and the initial amount of money."""
    def __init__(self):
        """intialize when program start, if it is not first time using, read in record from'record.txt'"""
        try:
            fh = open('record.txt','r')
            SaveLog = fh.readlines()
            self._records = []
            if SaveLog != []:
                a = SaveLog[0].replace("\n","")
                user_info = a.split(' ')
                self._username = user_info[0]
                self._account = user_info[1]
                self._password = user_info[2]
                for i,j in enumerate(SaveLog,start=1): #read in records
                    record = j.split(' ')
                    if len(record) == 5: #if valid input
                        try:
                            new_record = Record(record[0],int(record[1]),int(record[2]),int(record[3]),int(record[4]))
                            self._records.append(new_record)
                        except ValueError:
                            sys.stderr.write('Invalid value amount of money\nFail to laod record\n')
                    else: #if input cannot split
                        pass
                cnt = 0 # counter for how many time user type wrong account and password ,when cnt>=3 ,they can reset
                while True:
                    account = input('please enter your account: ')
                    password = input('please enter your password: ')
                    if account == self._account and password == self._password:
                        print(f'welcome back! {self._username}')
                        break
                    else:
                        print('Mismatch account and password, try again.\n')
                        cnt += 1
                    if cnt >= 3:
                        cmd = input('Forget password or account? press[A/P/B/N] to decide which do you want reset') #note that A stands for account , P stans for passwod, B stands for both,N stnads for no changes
                        if cmd == 'A':
                            new_account = input('please enter your new account: ')
                            self._account = new_account
                        elif cmd == 'P':
                            new_password = input('please enter your new password: ')
                            self._password = new_password
                        elif cmd == 'B':
                            new_account = input('please enter your new account: ')
                            self._account = new_account
                            new_password = input('please enter your new password: ')
                            self._password = new_password
                        elif cmd == 'N':
                            pass
                        else:
                            print('invalid command')
            else:
                print('Welcome to use our accounting program')
                self._username = input('What is your name? ')
                print('Since you first time use our program, you need to set up an account and password')
                self._account = input('Account: ')
                self._password = input('Password(You should include both uppercase,lowercase letter and nnmber): ')
                print('All set up , you can start using!')
            fh.close()
        except FileNotFoundError:
            sys.stderr.write("the text file 'record.txt' does not exist\n")
            exit(1)
 
    def add(self,record,categories):
        """add a record in the program"""
        log = record.split(' ')
        num = len(log)
        if num == 5:
            try:
                assert log[0] != ''
                #expense = int(log[2])
                if categories.is_category_valid(log[0]):
                    r = Record(log[0],int(log[1]),int(log[2]),int(log[3]),int(log[4]))
                    self._records.append(r)
                else:
                    sys.stderr.write("The specified category is not in the category list.\n")
                    sys.stderr.write("You can check the category list by command \"view categories\".\n")
                    sys.stderr.write("Fail to add a record.\n")
        
            except ValueError:
                sys.stderr.write('Invalid value for money.\n')
                sys.stderr.write('Fail to add a record.\n')
            except AssertionError:
                sys.stderr.write("The format of a record should be like this:'meal 50 2022 12 18'.\n")
            finally:
                    pass
        else:
            sys.stderr.write('The format of a record should be like this:"meal 50 2022 12 18".\n')
    def view(self):
        """view all the record stored in the varaiable 'records'"""
        # 1. Print all the records and report the balance.
        total = 0
        print("Here's your expense and income records:")
        print('Category        Amount/proportion     Date ')
        print('=============== ===================   ==============')
        for v in self._records:
            total += v.amount
        for v in self._records:
            percentage = v.amount/total
            print(f"{v.category}{' '*(15-len(v.category))} {v.amount}/{percentage*100:3.2f}%{' '*(21-len(str(v.amount))-5)}{v.year}/{v.month}/{v.day}") 
        print('=============== ===================   ==============')
        print(f'Now you have spent {total} dollars.')
    def delete(self,delete_record):
        """delete a record"""
        # 1. Define the formal parameter.
        # 2. Delete the specified record from self._records.
        log = delete_record.split(' ')
        delete = False
        if len(log) == 5:
            if delete == False:
                self._records.reverse()
                for v in self._records:
                    if v.category == log[0] and v.amount == int(log[1]) and v.year == int(log[2]) and v.month == int(log[3]) and v.day == int(log[4]):
                        self._records.pop(self._records.index(v))
                        delete = True
                        break
                self._records.reverse()
                if delete == False:
                    sys.stderr.write(f"There's no record with '{delete_record}'.\n")
                    sys.stderr.write('Fail to delete a record\n')
        else:
            sys.stderr.write('Invalid format. Fail to delete a record\n')
            #return records
    def find(self,target_categories):
        """find specific category and its subcategories while printing records in these categories"""
        # 1. Define the formal parameter to accept a non-nested list
        #    (returned from find_subcategories)
        # 2. Print the records whose category is in the list passed in
        #    and report the total amount of money of the listed records.
        #print(target_categories)
        sub_category_log = filter(lambda v: v.category in target_categories,self._records)
        total = 0
        try:
            print(f'Here\'s your expense and income records under category "{target_categories[0]}":')
            print('Category        Amount/proportion     Date ')
            print('=============== ===================   ==============')
            for v in sub_category_log:
                total += v.amount
            for v in sub_category_log:
                percentage = v.amount/total
                print(f"{v.category}{' '*(15-len(v.category))} {v.amount}/{percentage*100:3.2f}%{' '*(21-len(str(v.amount))-5)}{v.year}/{v.month}/{v.day}") 
            print('=============== ===================   ==============')
            print(f'The total amount spent in {target_categories[0]} is {total}.')
        except IndexError:
            sys.stderr.write("can't find specified category in the records")
    def save(self):
        """save the records in a text file if user enter'exit'"""
        # 1. Write the initial money and all the records to 'records.txt'.
        log=[]
        with open('record.txt','w') as fh:
            fh.write(f'{self._username} {self._account} {self._password}\n')
            for v in self._records:
                log.append(f'{v._category} {v._amount} {v._year} {v._month} {v._day}\n')
            fh.writelines(log)
class Categories:
    """Maintain the category list and provide some methods."""
    def __init__(self):
        """initialize what categories may be included"""
        # 1. Initialize self._categories as a nested list.
        self._categories =  ['expense', ['food', ['meal', 'snack', 'drink'], 'transportation',                            ['bus', 'railway','MRT','flight']], 'income', ['salary', 'bonus']]
    def view(self,level=-1):
        """view all categories and its subcategories"""
        #self.view_category(self._categories)
        def view_categories(categories,level = -1):
            """inner function of view , the recursion step is in this function"""
            if categories == None:
                return
            if type(categories) in {list,tuple}:
                for item in categories:
                    view_categories(item,level+1)
            else:
                print(f"{' '*4*level}-{categories}")
        view_categories(self._categories)
        # 1. Define the formal parameters so that this method
        #    can be called recursively.
        # 2. Recursively print the categories with indentation.
        # 3. Alternatively, define an inner function to do the recursion.
   
    def is_category_valid(self,category):
        """to verilfy if a specific category is in initialized categories,if found return True else False"""
        def valid(category,categories):
            """inner function of view , the recursion step is in this function"""
            if type(categories) == list:
                for sub_categories in categories:
                    found = valid(category,sub_categories)
                    if found == True:
                        return True
            return category == categories
        return valid(category,self._categories)

    def find_subcategories(self,category):
        """find specific category and its subcategories and store them in a list"""
        def find_subcategories_gen(category, categories, found=False):
            """inner function of view , the recursion step is in this function"""
            if type(categories) == list:
                for index, child in enumerate(categories):
                    yield from find_subcategories_gen(category, child,found)
                    if child == category and index + 1 < len(categories)                         and type(categories[index + 1]) == list:
                        # When the target category is found,
                        # recursively call this generator on the subcategories
                        # with the flag set as True.
                        yield from find_subcategories_gen(category, categories[index+1],True)
            else:
                if categories == category or found == True:
                    yield categories
        return find_subcategories_gen(category,self._categories,False)

categories = Categories()
records = Records()
while True:
    command = input('What do you want to do (add / view / delete / view categories  / exit)? ')
    if command == 'add': #add a record
        record = input('Add an expense or income record with category, amount, and year month day\n(separate by spaces):')
        records.add(record,categories)
    elif command == 'view': # view records
        records.view()
    elif command == 'delete':
        delete_record = input('Which record do you want to delete? ')
        records.delete(delete_record)
    elif command == 'exit':
        records.save()
        break
    elif command == 'view categories':
        categories.view()
    else:
        sys.stderr.write('Invalid command. Try again.\n')


# In[ ]:





# In[ ]:





# In[ ]:




