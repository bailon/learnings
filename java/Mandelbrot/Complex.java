/******************************************************************************
 * Universidade Federal de Pelotas
 * Ciência da Computação - Programação Orientada a Objetos
 * 
 * Grupo: Bruno Rodrigues, Eduardo Saffer, Marco Beckmann
 * Data: 3 de Dezembro de 2008
 *
 * Este programa tem o objetivo deresolver uma equação da fractal de Mandelbrot
 * utilizando Threads.
 *
 * Este arquivo define a classe Complex, para definir numeros complexos, que
 * contém uma parte real e outra imaginária.
 ******************************************************************************/


/**
 * Esta classe implementa um apoio para a utilização de números reais, onde ele
 * possui uma parte Real e outra parte Imaginária. Ela é utilizada no cálculo
 * da superfície de Mandelbrot.
 **/
public class Complex {
	double re;
	double im;
    
    public Complex (double real, double imag) {
        re = real;
        im = imag;
    }
    
    
    /**
     * Valor de retorno da classe
     **/
    public String toString () {
    	return new String("(" + re + ", " + im + ")");
    }
    
    /**
     * Retorna o valor absoluto
     **/
    public double abs () {
        return Math.sqrt(re * re + im * im);
    }
    
    /**
     * Soma um número complexo ao atual
     **/
    public Complex plus (Complex b) {
        double real = re + b.re;
        double imag = im + b.im;
        return new Complex(real, imag);
    }

    /**
     * Realiza uma iteração no número
     **/
    public Complex times (Complex b) {
        double real = re * b.re - im * b.im;
        double imag = re * b.im + im * b.re;
        return new Complex(real, imag);
    }
}
