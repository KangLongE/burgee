#define _CRT_SECURE_NO_WARNINGS
#define MAX_INDEX 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "note.h"

//note�� ���� �� Ȯ�� �Ϸ��� �� ������ ����

int main(int argc, char* argv) {
//argc ���� ����
//argv ����

	nl* n1;
//	note_name[MAX_INDEX]
//	num
//	[note.h]

	int success = 0;
	// ���� ����

	if (argc == 1) {
	//���ڸ� ���� ������

		n1 = check_note();
		//check_note ���� �Ͽ� ������ ���� n1���� ����
		// 	[note.c]	[npte.h]

		for (int i = 0; i < n1->num; i++) {
			printf("%s\n", n1[i].note_name);
			fflush(stdout);
		}
		//���丮�� �ִ� ���� ��� ���
	}
	else if (argc >= 2) {
	//���� �̸��� ���ڷ� �� ���
		
		success = create_note(argv[2]);
		//create_note ����
		//[note.c]	[npte.h]

		if (success) {
		//����
			printf("%s\n", argv[2]);
			fflush(stdout);
			printf("%d\n", success);
			fflush(stdout);
		}
		else {
		//����
			printf("%d\n", success);
			fflush(stdout);
		}
	}

}