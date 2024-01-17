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

