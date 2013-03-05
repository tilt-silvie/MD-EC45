/*************************************************************
2012�N 5/11�@�����쐬
*************************************************************/
//PIC30F C30 v3.31 & MPLAB v8.84


#ifndef	_CONFIG33F_H_
#define	_CONFIG33F_H_

_FBS(BWRP_WRPROTECT_OFF & BSS_NO_FLASH);

_FGS(GWRP_OFF & GSS_OFF);

_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);

_FOSC(POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_OFF & FCKSM_CSDCMD);

_FWDT(WDTPOST_PS32768 & WDTPRE_PR128 & WINDIS_OFF & FWDTEN_OFF);

_FPOR(FPWRT_PWR128 & ALTI2C_OFF);

_FICD(ICS_PGD1 & JTAGEN_OFF);


/*************************************************************
_FBS(�u�[�g�Z�O�����g�̕ی�̈�L��/���� & �u�[�g�R�[�h�Z�O�����g�̕ی��);

	�u�[�g�Z�O�����g�̕ی�̈�L��/����
		BWRP_WRPROTECT_ON    �u�[�g�Z�O�����g�̕ی�L��
	    BWRP_WRPROTECT_OFF   �u�[�g�Z�O�����g�̕ی얳��
	
	�u�[�g�R�[�h�Z�O�����g�̕ی��
		BSS_LARGE_FLASH_HIGH 
	    BSS_HIGH_LARGE_BOOT_CODEHigh
		BSS_MEDIUM_FLASH_HIGHHigh
		BSS_HIGH_MEDIUM_BOOT_CODEHigh
	    BSS_SMALL_FLASH_HIGH High 
	    BSS_HIGH_SMALL_BOOT_CODEHigh 
	    BSS_LARGE_FLASH_STD  
	    BSS_STRD_LARGE_BOOT_CODEStandard 
	    BSS_MEDIUM_FLASH_STD Standard 
	    BSS_STRD_MEDIUM_BOOT_CODEStandard 
	    BSS_SMALL_FLASH_STD  Standard 
	    BSS_STRD_SMALL_BOOT_CODEStandard 
	    BSS_NO_FLASH        				 �F�ی�̋@�\����
	    BSS_NO_BOOT_CODE				     �F�ی�̋@�\����
		
_FGS(�R�[�h�v���e�N�g�̗L�� & �R�[�h�v���e�N�g�̗̈�);

	�R�[�h�v���e�N�g�̗L��
		GWRP_ON		�F�R�[�h�v���e�N�g����
		GWRP_OFF	�F�R�[�h�v���e�N�g�Ȃ� 
		
	�R�[�h�v���e�N�g�̗̈�Ȃ�
		GSS_HIGH    
	    GSS_STD     
	    GCP_ON      
	    GSS_OFF     �F�R�[�h�v���e�N�g�̗̈�Ȃ�
	    GCP_OFF		�F�R�[�h�v���e�N�g�̗̈�Ȃ�

_FOSCSEL(���M����PLL�̗L��/���� & FRC�ŃX�^�[�g�A�b�v���A���[�U�[�I���̔��U�킪���f�B�ɂȂ������̎����؂�ւ��̗L��/����);

	���M����PLL�̗L��/����
		FNOSC_FRC            �F�������M(FRC)
	    FNOSC_FRCPLL         �F�������M (FRC) PLL���I��
	    FNOSC_PRI            �F�O�����M (XT, HS, EC)
	    FNOSC_PRIPLL         �F�O�����M (XT, HS, EC) PLL���I��
	    FNOSC_SOSC           �F(SOSC)
	    FNOSC_LPRC           �F(LPRC)
	    FNOSC_FRCDIV16       �F�������M(FRC/16)
	    FNOSC_LPRCDIVN       �F�������M(FRC/N)
	
	���M�@�̎����؂芷���̗L��/����
		IESO_OFF             �F���[�U�[�I���̔��M��ŃX�^�[�g
		IESO_ON              �FFRC�ŃX�^�[�g�A�b�v���A���[�U�[�I���̔��U�킪���f�B�ɂȂ������Ɏ����I�ɐ؂�ւ���


_FOSC(�唭�U��̑I�� & OSC2�s���̋@�\�I�� & I/O�s���̍ăR���t�B�M�����[�V�����̗L��/���� & �N���b�N�؂�ւ��ݒ�);

	�唭�U��̑I��
 
		POSCMD_EC            �F�唭�M��I��(EC 0.8~64MHz)
		POSCMD_XT            �F�唭�M��I��(XT 3MHz~10Mhz)
		POSCMD_HS            �F�唭�M��I��(HS 10MHz~40MHz)
		POSCMD_NONE          �F�唭�M��I�t
 	
	OSC2�s���̋@�\�I��
 		OSCIOFNC_ON          �FOSC2�͔ėpIO�ɐݒ�
		OSCIOFNC_OFF         �FOSC2�̓N���b�N�o�͂ɐݒ�
	
	I/O�s���̍ăR���t�B�M�����[�V�����̗L��/����
		IOL1WAY_OFF          �FI/O�s���̍ăR���t�B�M�����[�V�����̗L��
	    IOL1WAY_ON           �FI/O�s���̍ăR���t�B�M�����[�V�����̖���
		
	�N���b�N�؂�ւ��@�\�̗L��
 		FCKSM_CSDCMD  		 �F�Ƃ���OFF 
		FCKSM_CSECMD		 �F�N���b�N�؂�ւ��͉B�t�F�C���Z�[�t�E�N���b�N���j�^�[��OFF 
		FCKSM_CSECME		 �F�Ƃ���ON
	
_FWDT(�|�X�g�X�P�[���̐ݒ� & �v���X�P�[���̐ݒ� & �E�H�b�`�h�b�O�^�C�}�̗L��/����);

	�|�X�g�X�P�[���̐ݒ�
		WDTPOST_PS1          1:1
		WDTPOST_PS2          1:2
	    WDTPOST_PS4          1:4
	    WDTPOST_PS8          1:8
	    WDTPOST_PS16         1:16
		WDTPOST_PS32         1:32
	    WDTPOST_PS64         1:64
	    WDTPOST_PS128        1:128
	    WDTPOST_PS256        1:256
	    WDTPOST_PS512        1:512
	    WDTPOST_PS1024       1:1,024
	    WDTPOST_PS2048       1:2,048
	    WDTPOST_PS4096       1:4,096
	    WDTPOST_PS8192       1:8,192
	    WDTPOST_PS16384      1:16,384
	    WDTPOST_PS32768      1:32,768
	
	�v���X�P�[���̐ݒ�
		WDTPRE_PR32			1:32
	    WDTPRE_PR128       	1:128
		
	�E�H�b�`�h�b�O�^�C�}�̗L��/����
		FWDTEN_ON		�F�E�H�b�`�h�b�O�^�C�}�L�� 
		FWDTEN_OFF		�F�E�H�b�`�h�b�O�^�C�}����
	
_FPOR(�p���[�I�����Z�b�g�̃p���X�� & I2C�s���̐ݒ�);	

	�p���[�I�����Z�b�g�̃p���X��
		FPWRT_PWR1		�F�p���[�I�����Z�b�g���g�p���Ȃ��i�u���E���A�E�g���Z�b�g�̂݁j 
		FPWRT_PWR2		�F2msec�̃p���X�� 
		FPWRT_PWR4		�F4msec�̃p���X�� 
		FPWRT_PWR8		�F8msec�̃p���X��
		FPWRT_PWR16		�F16msec�̃p���X�� 
		FPWRT_PWR32		�F32msec�̃p���X�� 
		FPWRT_PWR64		�F64msec�̃p���X��
		FPWRT_PWR128	�F128msec�̃p���X�� 

	I2C�s���̐ݒ�
		ALTI2C_ON            I2C��ASDA1/ASCL1
	    ALTI2C_OFF           I2C��SDA1/SCL1

_FICD(�R�~���j�P�[�V�����|�[�g�̑I�� & JTAG Port�̑I��);
	�R�~���j�P�[�V�����|�[�g�̑I��
		ICS_PGD3             PGC3/EMUC3 and PGD3/EMUD3
	    ICS_PGD2             PGC2/EMUC2 and PGD2/EMUD2
	    ICS_PGD1             PGC1/EMUC1 and PGD1/EMUD1

	JTAG Port�̑I��
	    JTAGEN_OFF           JTAG�͖���
	    JTAGEN_ON            JTAG�͗L��
*************************************************************/
	
#endif	/* _CONFIG33F_H_ */
