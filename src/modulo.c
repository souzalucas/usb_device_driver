#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lucas Souza Santos");
MODULE_DESCRIPTION("Este driver reconhece a conexão e desconexão de um ou mais dispositivos USBs específicos");

// Eh chamada quando o dispositivo for conectado
static int dispositivo_conectado(struct usb_interface *interface, const struct usb_device_id *id) {
  printk(KERN_INFO "[*] Dispositivo (%04X:%04X) conectado\n", id->idVendor, id->idProduct);
  return 0;
}

// Eh chamada quando o dispositivo for desconectado
static void dispositivo_desconectado(struct usb_interface *interface) {
  printk(KERN_INFO "[*] Dispositivo desconectado\n");
}

// Estrutura do dispositivo USB
static struct usb_device_id tabela_do_dispositivo[] = {
  // HD externo
  { USB_DEVICE(0x13fd, 0x3920) },     // Informacao obtida atraves do comando "lsusb"
  // Smartphone Samsung
    { USB_DEVICE(0x04e8, 0x6860) },
  // Dispositivo Multilaser (mouse e teclado)
  { USB_DEVICE(0x062a, 0x4c01) },
  {} // a estrutura usb_device_id deve terminar com uma entrada NULL 
};

MODULE_DEVICE_TABLE(usb, tabela_do_dispositivo); // Exportando tabela de IDs de dispositivos para o user space

// Driver do dispositivo que será fornecido ao kernel
static struct usb_driver driver_do_dispositivo = {
  .name = "Identificador de Dispositivo USB v1.0",
  .id_table = tabela_do_dispositivo,
  .probe = dispositivo_conectado,
  .disconnect = dispositivo_desconectado
};

static int __init iniciar_modulo(void) {
  int ret = -1;
  printk(KERN_INFO "Registrando driver de dispositivo USB");
  ret = usb_register(&driver_do_dispositivo);
  printk(KERN_INFO "\tDriver registrado com sucesso");
  return ret;
}

static void __exit remover_modulo(void) {
  printk(KERN_INFO "Removendo driver de dispositivo USB");
  usb_deregister(&driver_do_dispositivo);
  printk(KERN_INFO "\tDriver Removido com sucesso");
}

module_init(iniciar_modulo);
module_exit(remover_modulo);
