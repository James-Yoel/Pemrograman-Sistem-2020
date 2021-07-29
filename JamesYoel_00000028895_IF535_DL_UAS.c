#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t room;
sem_t chopstick[5];

void * philosopher(void *);
void eat(int);
int main()
{
	int i,a[5];
	pthread_t tid[5];
	//Inisialisasi semaphore untuk room dengan pshared = 0 untuk thread dan inisialisasi nilai semaphore = 4
	sem_init(&room,0,4);
	//Untuk setiap philosopher inisialisasi semaphore sumpit dengan pshared = 0 untuk thread dan inisialisasi nilai semaphore sumpit = 1
	for(i=0;i<5;i++){
		sem_init(&chopstick[i],0,1);
	}
	//Untuk setiap philosopher dibuatnya thread yang menjalankan fungsi void * philosopher yang mengirim argumen berupa a[i]	
	for(i=0;i<5;i++){
		a[i]=i;
		pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);
	}
	//Untuk setiap philosopher dilakukkannya join thread
	for(i=0;i<5;i++){
		pthread_join(tid[i],NULL);
	}
}

void * philosopher(void * num)
{
	//Looping agar program tidak berhenti dan philosopher yang sudah selesai makan bisa kembali
	while(1){
		//Inisialisasi phil sesuai dengan argumen dari pthread_create
		int phil=*(int *)num;
		//Nilai semaphore room diturunkan menandakan philosopher masuk ruangan
		//Jika semaphore 0, tunggu sampai semaphore dinaikkan
		sem_wait(&room);
		printf("\nPhilosopher %d has entered room",phil);
		//Nilai semaphore untuk sumpit bagian kiri dan kanan philosopher diturunkan menandakan sumpit tersebut telah diambil
		//Jika salah satu sumpit semaphore bernilai 0, tunggu sampai dinaikkan
		sem_wait(&chopstick[phil]);
		sem_wait(&chopstick[(phil+1)%5]);
		//Philosopher makan selama 3 detik
		eat(phil);
		sleep(3);
		//Philosopher selesai makan
		printf("\nPhilosopher %d has finished eating",phil);
		//Sumpit kiri dan kanan sudah selesai digunakan, semaphore dinaikkan menandakan sumpit tersebut sudah selesai dipakai
		sem_post(&chopstick[(phil+1)%5]);
		sem_post(&chopstick[phil]);
		//Semaphore dinaikkan menandakan philosopher sudah keluar dari ruangan
		sem_post(&room);
		//Menunggu 5 detik agar philosopher tidak langsung kembali 
		sleep(5);
	}
}

void eat(int phil)
{
	//Philosopher sedang makan
	printf("\nPhilosopher %d is eating",phil);
}