package org.example;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

class MyLinkedList {
    private Node head;
    private ArrayList<Integer> blackList;

    /* Linked list Node*/
    static class Node {
        int ID;
        int punctaj;
        Node right;
        Node left;

        Node(int ID_n, int punctaj_n) {
            this.ID = ID_n;
            this.punctaj = punctaj_n;
        }
    }

    public MyLinkedList(){
        head = new Node(0, 0);
        head.right = new Node(0, 0);
        head.left = null;
        head.right.left = head;
        head.right.right = null;

        blackList = new ArrayList<>();
    }

    public void insert(int ID, int punctaj) {
        if(blackList.contains(ID)){
            return;
        }
        Node current = this.head.right;
        Node new_node = new Node(-1, -1);
        boolean found = false;

        while(current.ID != 0){
            if(current.ID == ID){
                current.punctaj += punctaj;
                current.left.right = current.right;
                current.right.left = current.left;

                new_node = current;
                found = true;
                break;
            }
            current = current.right;
        }

        if(!found) {
            new_node = new Node(ID, punctaj);
        }

        // sanity check
        if(new_node.ID <= 0){
            System.out.println("Invalid node!\n");
            return;
        }

        Node iterator = this.head.right;
        while(iterator.punctaj > new_node.punctaj && iterator.ID != 0){
            iterator = iterator.right;
        }
        new_node.left = iterator.left;
        new_node.right = iterator;
        iterator.left.right = new_node;
        iterator.left = new_node;
    }

    public void remove(int ID){
        blackList.add(ID);
        Node current = this.head.right;

        while(current.ID != 0){
            if(current.ID == ID){
                current.left.right = current.right;
                current.right.left = current.left;
            }
            current = current.right;
        }
    }

    public void print(){
        try {
            FileWriter myWriter = new FileWriter("Clasament.txt");
            Node current = this.head.right;
            while(current.ID != 0){
                myWriter.write(current.ID + "," + current.punctaj + '\n');
                current = current.right;
            }
            myWriter.close();
        } catch (IOException e) {
            System.out.println("An error occurred while writing to file.");
            e.printStackTrace();
        }
    }
}