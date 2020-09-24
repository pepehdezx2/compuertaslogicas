#define S_BUSY 		0x80
#define S_ACK 		0x40
#define S_PAPER_END 0x20
#define S_SELECT_IN 0x10
#define SnError     0x08

NTSTATUS DispatchRead(PDEVICE_OBJECT fdo, PIRP Irp){
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	PUCHAR pDato = (PUCHAR) Irp->AssociatedIrp.SystemBuffer;
	unsigned char aux, casicasi;
	unsigned char MASK_CTL=0x0B;
	aux = READ_PORT_UCHAR((unsigned char *)pdx->portBase+2)^MASK_CTL;
	casicasi = aux & 0xFE;
	WRITE_PORT_UCHAR((unsigned char *)pdx->portBase+2,casicasi^MASK_CTL);
	unsigned char input=0xFF;
	WRITE_PORT_UCHAR((unsigned char*)pdx->portBase,input);
	casicasi = aux | 0x01;
	WRITE_PORT_UCHAR((unsigned char*)pdx->portBase+2,casicasi^MASK_CTL);
	unsigned char MASK_STATUS = 0x80;
	unsigned char mask[] ={S_BUSY, S_PAPER_END, S_SELECT_IN, SnError}
	unsigned char dato = 0;
	unsigned char auxr = 0x01;
	unsigned char status, control;
	unsigned int  i;
	for(i=0; i<4; i++, aux<<=1){
    if(i == 0){
      control = READ_PORT_UCHAR((unsigned char *)0x37A)^MASK_CTL;
      control& = 0xF7;
      WRITE_PORT_UCHAR((unsigned*)0x37A, control^MASK_CTL);
      Sleep(100);}
      status = READ_PORT_UCHAR((unsigned char *)0x379)^MASK_CTL;
      if((status&mask[i])!=0)
        dato = dato|auxr;
    }
    dato = dato & 0x0F
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 1;
	*pDato = dato;
	return STATUS_SUCCESS;
}