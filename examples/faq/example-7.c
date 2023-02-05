#include <stdio.h>
#include <libakrypt.h>
#include <libakrypt-base.h>

int main() {
    /*Структура для хранения контекста ключа*/
    struct bckey key;

    /*Значение контекстного ключа вырабатывается из данного пароля*/
    char password[] = "password";
    /*Случайный вектор в виде строки символов*/
    char s[] = "sugar";

    /*Инициализация секретного ключа алгоритма блочного шифрования Кузнечик*/
    if (ak_error_ok != ak_bckey_create_kuznechik(&key))
	return ak_error_get_value();	

    /*Структура для хранения случайного (псевдослучайного) значения*/
    struct random rand;
    /*Создание случайного (псевдослучайного) значения NLFSR генератором*/
    ak_random_create_nlfsr(&rand);

    /*Присваивание контексту ключа алгоритма блочного шифрования случайное (псевдослучайное)
    значение, вырабатываемое заданным генератором случайных (псевдослучайных) чисел.*/
    if(ak_error_ok != ak_bckey_set_key_random(
    			&key, /* Контекст ключа алгоритма блочного шифрования */
			&rand /* Контекст генератора случайных (псевдослучайных) чисел */
			))
	return ak_error_get_value();
	
    /*Текст для зашифрования*/
    char data[128] = "test data for encrypt";
    /*Область памяти, куда помещается зашифрованная строка*/
    char out[128];
    /*Синхропосылка*/
    ak_uint8 openssl_ivcbc[32] = {
		0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xce, 0xf0, 0xa1, 
		0xb2, 0xc3, 0xd4, 0xe5, 0xf0, 0x01, 0x12,
		0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 
		0x90, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
		0x18, 0x19
	};

    /* Зашифрование текста в режиме простой замены с зацеплением */
    if(ak_error_ok != ak_bckey_encrypt_cbc(
		&key, 			/* Контекст ключа алгоритма блочного шифрования */
		data, 			/* Указатель на область памяти, где хранятся данные для зашифрования */
		out,  			/* Указатель на область памяти, куда помещаются зашифрованные данные */
		128,  			/* Размер зашифровываемых данных (в байтах) */
		openssl_ivcbc, 		/* Указатель на произвольную область памяти - синхропосылку */
		sizeof(openssl_ivcbc) 	/* Длина синхропосылки в байтах. Согласно  стандарту ГОСТ Р 34.13-2015 длина синхропосылки 
						должна быть ровно в два раза меньше, чем длина блока, то есть 4 байта для Магмы и 8 байт для Кузнечика.*/
		))
	return ak_error_get_value();

    /*Область памяти, куда помещается расшифрованная строка*/
    char decrypt[128];
    /* Расшифрование текста в режиме простой замены с зацеплением */
    if (ak_error_ok != ak_bckey_decrypt_cbc(
		&key, 			/* Контекст ключа алгоритма блочного шифрования*/
		data, 			/* Указатель на область памяти, где хранятся данные для зашифрования */
		out,  			/* Указатель на область памяти, куда помещаются зашифрованные данные */
		128,   			/* Размер зашифровываемых данных (в байтах) */
		openssl_ivcbc, 		/* Указатель на произвольную область памяти - синхропосылку */
		sizeof(openssl_ivcbc)   /* Длина синхропосылки в байтах. Согласно  стандарту ГОСТ Р 34.13-2015 длина синхропосылки 
						должна быть ровно в два раза меньше, чем длина блока, то есть 4 байта для Магмы и 8 байт для Кузнечика.*/
		))
	return ak_error_get_value();

    if (!memcmp(data, decrypt, sizeof(data)))
	    return 0;

    return -1;
}
