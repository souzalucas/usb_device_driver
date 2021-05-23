#include <linux/module.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alan Patriarca e Lucas Souza");
MODULE_DESCRIPTION("Este driver reconhece a conexão e desconexão de um ou mais dispositivos USBs específicos");

// Funcao chamada quando algum dispositivo registrado for conectado
static int dispositivo_conectado(struct usb_interface *interface, const struct usb_device_id *id) {
  printk(KERN_INFO "[*] Dispositivo (%04X:%04X) conectado\n", id->idVendor, id->idProduct);
  return 0;
}

// Funcao chamada quando algum dispositivo registrado for desconectado
static void dispositivo_desconectado(struct usb_interface *interface) {
  printk(KERN_INFO "[*] Dispositivo desconectado\n");
}

// Estrutura dos dispositivos USB
static struct usb_device_id tabela_de_dispositivos[] = {
  // HD externo
  { USB_DEVICE(0x13fd, 0x3920) },     // Informacao obtida atraves do comando "lsusb" no linux
  // Smartphone Samsung
  { USB_DEVICE(0x04e8, 0x6860) },
  // Dispositivo Multilaser (mouse e teclado)
  { USB_DEVICE(0x062a, 0x4c01) },
  {} // A estrutura usb_device_id deve terminar com uma entrada NULL 
};

// Exportando tabela de IDs de dispositivos para o espaco de usuario
MODULE_DEVICE_TABLE(usb, tabela_de_dispositivos);

// Driver de dispositivo que sera fornecido ao kernel
static struct usb_driver driver_de_dispositivo = {
  .name = "Identificador de Dispositivo USB v1.0",
  .id_table = tabela_de_dispositivos,
  .probe = dispositivo_conectado,
  .disconnect = dispositivo_desconectado
};

// Executa ao inicializar modulo
static int __init iniciar_modulo(void) {
  int ret = -1;
  printk(KERN_INFO "Registrando driver de dispositivo USB");
  ret = usb_register(&driver_de_dispositivo);
  if (ret) {
    printk("\tFalha ao registrar módulo, erro número %d", ret);
  } else {
    printk(KERN_INFO "\tDriver registrado com sucesso");
  }
  return ret;
}

// Executa ao descarregar modulo
static void __exit descarregar_modulo(void) {
  printk(KERN_INFO "Descarregando driver de dispositivo USB");
  usb_deregister(&driver_de_dispositivo);
  printk(KERN_INFO "\tDriver descarregado com sucesso");
}

module_init(iniciar_modulo);
module_exit(descarregar_modulo);
