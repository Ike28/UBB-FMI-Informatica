## Grile practic Cloud Applications Architecture - Solutii
> link prescurtat 👀: [bit.ly/grileaws](https://bit.ly/grileaws)

> Folositi pagina in light mode ☀️ pentru o experienta mai buna

#### 1. Due to regulatory requirements, your team must inspect all packets that flow into your system. What load balancer can help you achieve this?
- [ ] Network Load Balancer
- [x] ___Gateway Load Balancer___
- [ ] None. This can only be achieved using VPC features
- [ ] Application Load Balancer
<br>

#### 2. The most cost-effective and scalable way to host a static web application on AWS is:
- [x] ___Simple Storage Service (S3)___
- [ ] Elastic Compute Cloud (EC2)
- [ ] Elastic Container Service (ECS)
<br>

#### 3. Your system requires a load-balancing solution that preserves the source IP address. Which solution should you choose?
- [ ] Setup a custom load balancer using NGINX or HAProxy
- [ ] Gateway Load Balancer
- [x] ___Network Load Balancer___
- [ ] Application Load Balancer
<br>

#### 4. CloudFront is a(n) ___```    CDN    ```___ and is composed of ___```    a network of edge locations    ```___
<br>

#### 5. An AWS Region is:
- [ ] An organizational unit designed to serve clients from a specific area
- [ ] An AWS data center
- [x] ___An independent and isolated cloud deployed in a specific geographical location___
<br>

#### 6. Which service models does Amazon Web Services provide?
- [x] ___PaaS___
- [x] ___SaaS___
- [x] ___IaaS___
<br>

#### 7. What is CloudFormation?
- [ ] PaaS Service
- [x] ___IaC Service___
- [ ] IaaS Service
- [ ] None of the above
<br>

#### 8. VPCs allow you to control the traffic between ___```    (sub)networks    ```___ and use ___```    private IPs    ```___
<br>

#### 9. An EC2 instance runs in a specific ___```    VPC subnet    ```___ based on which ___```    both public and private    ```___ IP addresses are assigned to the instance
<br>

#### 10. Security groups act at the ___```    instance    ```___ level, not the ___```    subnet    ```___ level
<br>

#### 11. You are designing a three-tier web application and want to restrict access to the database tier (remember PostgreSQL instance) to accept traffic from the application servers only (Spring Java app). However, these application servers are in an Auto Scaling group and may vary in quantity. How should you configure the database servers to meet the requirements?
- [ ] Configure the database security group to allow database traffic from the application server IP addresses.
- [x] ___Configure the database security group to allow database traffic from the application server security group.___
- [ ] Configure the database subnet network ACL to deny all inbound non-database traffic from the application-tier subnet.
- [ ] Configure the database subnet network ACL to allow inbound database traffic from the application-tier subnet.
<br>

#### 12. The connection times out while trying to access an EC2 instance via SSH on the standard port. What is the most likely issue?
- [ ] The instance is not reachable via the internet.
- [ ] The instance type is misconfigured.
- [x] ___The security group does not explicitly allow traffic on port 22.___ 
<br>

#### 13. Content stored on S3 can be restricted such that it's accessible only through CloudFront by using:
- [ ] Signed URLs
- [ ] S3 Bucket Settings
- [x] ___Origin Access Identity___
<br>

#### 14. From wher does Docker pull the image `hello-world` when running 
```cobol
      docker run hello-world
```
- [x] ___Docker tries to find it locally. If it doesn't find it, Docker checks the Docker Hub___
- [ ] From the registry specified in the Dockerfile from the current directory
- [ ] Always pulls it from the Docker Hub
- [ ] Docker tries to pull it from AWS ECR
<br>

#### 15. The AWS service for load balancing supports the following types of load balancers:
- Application Load Balancer which operates at ___```    OSI layer 7 (HTTP/WebSocket)    ```___
- Network Load Balancer which operates at ___```    OSI layer 4 (TCP/UDP)    ```___
- Gateway Load Balancer which operates at ___```    OSI layer 3 (Network)    ```___
<br>

#### 16. Simple Storage Service (S3) helps us:
- [ ] Host web applications
- [ ] Create bootable virtual disks that can be attached to EC2 instances
- [x] ___Store and serve an infinite amount of objects such as images, documents and videos___ 
<br>

#### 17. RDS is a:
- [ ] managed container service
- [x] ___managed relational database service___
- [ ] serverless database
<br>

#### 18. Documents are stored in S3 in a:
- [ ] Server
- [x] ___Bucket___
- [ ] Storage account
<br>

#### 19. An EC2 instance can be configured as follows:
- [x] ___Based on an instance type which offers certain resources (vCPU, RAM, networking etc.)___
- [ ] Each resources must always be specified independently based on the estimated workload
- [ ] There is no need to configure anything. The instance will scale based on the workload
<br>

#### 20. Software can be automatically installed during the provisioning of the EC2 instance through ___```    User Data    ```___ which is composed of ___```   a series of shell commands   ```___
<br>

#### 21. Simple Storage Service (S3) works through:
- [x] ___HTTP___
- [ ] SMTP
- [ ] FTP
<br>

#### 22. An EC2 instance is deployed in a specific Availability Zone (AZ)
- [x] ___True___
- [ ] False
<br>

#### 23. Docker is a:
- [ ] framework
- [ ] programming language
- [x] ___container engine___
- [ ] virtualization program
<br>

#### 24. Your application tier is running an Auto-Scaling Group and you need to change the instance type. In which of the following areas can this be achieved?
- [x] ___Auto-scaling launch template configuration___
- [ ] Auto-scaling policy configuration
- [ ] Auto-scaling AMI
- [ ] Auto-tags configuration
<br>

#### 25. Objects stored in S3 can be made public by configuration of the ___```    bucket policy    ```___ ___```    at any time    ```___
<br>

#### 26. What is the role of a service within ECS?
- [ ] It orchestrates the underlying EC2 instances
- [ ] There is no "service" concept, only tasks and task definitions
- [ ] It load balances traffic
- [x] ___It ensures that the configured number of containers/tasks is running at all times___
<br>

#### 27. How does ECS ensure the cluster has enough computing capacity when running on EC2?
- [ ] ECS only works with Fargate, not with EC2
- [ ] You have to manually scale the cluster
- [x] ___It leverages an ASG___
- [ ] It has its own instance orchestrator
<br>

#### 28. ECS is a service for running
- [x] ___containers in a managed way___
- [ ] RDBMS
- [ ] virtual machines
<br>

#### 29. How does ECS know how to run a container/task?
- [ ] Based on the images you mention during the cluster creation
- [ ] ECS will run all images from the configured ECR repository
- [ ] Based on the provided Dockerfile
- [x] ___Based on the configured task definition___
<br>

#### 30. Your system uses an Application Load Balancer (ALB). For audit purposes, you must store the IP address of the clients. What is the simplest approach?
- [ ] The ALB already preserves the client's IP address
- [ ] Replace the ALB with a Network Load Balancer
- [x] ___Get the client's IP address from the `x-forwarded-for` header___
<br>

#### 31. Why are there multiple Availability Zones in one region?
- [ ] Becayse cross-region application is not supported since AWS regions are independent cloud deployments
- [x] ___To enable highly available architectures and redundant storage___
- [ ] Because one AZ would not support all IP addresses for a VPC
<br>

#### 32. RDS can:
- [x] ___backup the database automatically___
- [x] ___upgrade the RDBMS automatically___
- [x] ___encrypt the data___
<br>

#### 33. What is the purpose of the _Dockerfile_ for Docker?
- [ ] It contains the input data for a program that runs within a container
- [x] ___It contains all the commands and steps for assembling a Docker image___
- [ ] It contains the output after running a container
- [ ] Docker doesn't use the Dockerfile
<br>

#### 34. Every instance in a subnet in a VPC can have assigned a different set of ___```    security groups    ```___
<br>

#### 35. If you need just one EC2 instance, would an Auto-Scaling Group (ASG) provide any benefit?
- [x] ___Yes, the ASG will ensure there is always one instance running___
- [ ] No, it will just incur unnecessary costs
- [ ] Yes, it will scale the resources (CPU & RAM) of the instance as needed
- [ ] You cannot run an EC2 instance without an ASG
<br>

#### 36. You can choose the AZ in which an EC2 will run by:
- [ ] EC2 instances are AZ-agnostic
- [ ] Choosing the AZ during the instance configuration
- [x] ___Selecting a subnet for that specific AZ___
- [ ] You can choose the AZ only when using ASGs
<br>

#### 37. The most cost-effective and scalable way to host a static web application on AWS is:
- [x] ___Simple Storage Service (S3)___
- [ ] Elastic Compute Cloud (EC2)
- [ ] Elastic Container Service (ECS)
<br>

#### 38. What is the difference between a Docker image and a Docker container?
- [x] ___Containers are running instances of the images___
- [ ] There is no such thing as a Docker image
- [ ] An image groups multiple containers that can communicate between them
- [ ] They are the same
<br>

#### 39. An EC2 instance can be secured by using ___```    security groups    ```___ which ___```    control the inbound and outbound traffic    ```___
<br>

#### 40. CloudFront can serve the following:
- [x] ___Content stored on S3___
- [x] ___HTTP traffic from the Applications hosted on other providers___
- [x] ___HTTP traffic from API Gateway___
<br>

#### 41. Your team is sharing an AWS VPC with another team, so you configured a dedicated subnet with the CIDR 172.31.1.0/28. Your application is running on EC2 instances managed by an ASG. As the demand for your app increases, you notice that new EC2 instances are not created, even though the ASG is correctly configured. What is the most probable cause?
- [ ] You've set a budget limit that is preventing additional costs
- [ ] The load balancer has reached the maximum number of targets
- [ ] AWS ran out of capacity for that specific region
- [x] ___There are no more IP addresses available in the subnet___
<br>
