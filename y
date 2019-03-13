public Result StartAlgorithm(Instance instance){

        Result tempResult=new Result();
        float[] array=new float[instance.getNumberOfItems()];
        for(int i=0;i<instance.getNumberOfItems();i++)
        {
            array[i]=instance.selectItemAt(i).getRatio();
        }
        System.out.println("Przed sortowaniem");
        for(int i=0;i<instance.getNumberOfItems();i++)
        {
            System.out.println("nazwa "+instance.selectItemAt(i).getName()+"ratio: "+instance.selectItemAt(i).getRatio());
        }
        Arrays.sort(array);
        ArrayList<Item> tempList=new ArrayList<>();
        for(int i=0;i<instance.getNumberOfItems();i++)
        {
            for(int j=0;j<instance.getNumberOfItems();j++)
            {
                if(array[i]==instance.selectItemAt(j).getRatio())
                {
                    tempList.add(i,instance.selectItemAt(j));
                    break;
                }
            }

        }
        instance.setItems(tempList);
        System.out.println("po sortowaniu");
        for(int i=instance.getNumberOfItems()-1;i>=0;i--)
        {
            System.out.println("nazwa "+instance.selectItemAt(i).getName()+"ratio: "+instance.selectItemAt(i).getRatio());
        }

        return bestResult;
    }
