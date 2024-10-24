#pragma once
#include <cmath>
#define NULL_TELEM -1
#define EMPTY_POSITION -999999
#define DELETED_POSITION 888999
typedef int TElem;

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

    private:
		/* aici e reprezentarea */
        TElem* elemente;
        int capacitate;
        int dimensiune;

        int hashFunction1(TElem elem) const{
            return elem % this->capacitate;
        }
        int hashFunction2(TElem elem) const{
            return 1 + (elem % (this->capacitate - 1));
        }

        int doubleHash(TElem elem) const{
            int aux_elem = abs(elem);
            int probe_number = 0;
            int position = -1;
            bool gasit = false;
            while (!gasit){
                position = (this->hashFunction1(aux_elem) + probe_number * this->hashFunction2(aux_elem)) % this->capacitate;
                if (this->elemente[position] == EMPTY_POSITION || this->elemente[position] == DELETED_POSITION){
                    gasit = true;
                }
                else{
                    probe_number++;
                    if (probe_number >= this->capacitate){
                        return -1;
                    }
                }
            }
            return position;
        }
        void resize();

    public:
 		//constructorul implicit
		Multime();

		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		bool adauga(TElem e);

		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		bool sterge(TElem e);

		//verifica daca un element se afla in multime
		bool cauta(TElem elem) const;


		//intoarce numarul de elemente din multime;
		int dim() const;

		//verifica daca multimea e vida;
		bool vida() const;

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

        int get_capacitate() const{
            return this->capacitate;
        }
        const TElem* get_elemente() const{
            return elemente;
        }
		// destructorul multimii
		~Multime();
};




